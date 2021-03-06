/*
 * Copyright (c) 2002-2005 The RapidSvn Group.
 * Copyright (c) 2005-2009 by Rajko Albrecht (ral@alwins-world.de)
 * Copyright (c) 2011 Tim Besard <tim.besard@gmail.com>
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program (in the file LGPL.txt); if not,
 * write to the Free Software Foundation, Inc., 51 Franklin St,
 * Fifth Floor, Boston, MA 02110-1301 USA
 */
 
// subversion api
#include <subversion-1/svn_path.h>

// apr api
#include <apr_file_io.h>

// svncpp
#include "path.h"
#include "pool.h"
#include "url.h"
#include "revision.h"
#include "exception.h"

#include <qurl.h>

namespace svn
{
  Path::Path (const char * path)
  {
    init(QString::fromUtf8(path));
  }

  Path::Path (const QString & path)
  {
    init (path);
  }

  Path::Path (const Path & path)
    : m_path(path.m_path)
  {
  }

  void
  Path::init (const QString& path)
  {
    Pool pool;

    if (path.isEmpty()) {
      m_path = "";
    } else {
      const char * int_path = svn_path_internal_style (path.toUtf8(), pool.pool () );
      if (Url::isValid(path) ) {
        if (!svn_path_is_uri_safe(int_path)) {
            int_path = svn_path_uri_encode(int_path,pool);
        }
      }
      m_path = QString::fromUtf8(int_path);
      if (Url::isValid(path) && m_path.indexOf("@")!=-1 ) {
        /// @todo make sure that "@" is never used as revision parameter
        QUrl uri = m_path;
        m_path = uri.path();
        m_path.replace('@',"%40");
        m_path = uri.scheme()+"://"+uri.authority()+m_path;
        if (m_path.endsWith('/')) {
            int_path = svn_path_internal_style (path.toUtf8(), pool.pool () );
            m_path = QString::fromUtf8(int_path);
        }
      }
    }
  }

  bool Path::isUrl()const
  {
      return Url::isValid(m_path);
  }

  const QString &
  Path::path () const
  {
    return m_path;
  }

  Path::operator const QString&()const
  {
    return m_path;
  }

  QString Path::prettyPath()const
  {
    if (!Url::isValid(m_path)) {
        return m_path;
    }
    Pool pool;
    const char * int_path = svn_path_uri_decode(m_path.toUtf8(), pool.pool () );
    QString _p = QString::fromUtf8(int_path);
    _p.replace("%40","@");
    return _p;
  }

  const QByteArray
  Path::cstr() const
  {
    return m_path.toUtf8();
  }

  Path&
  Path::operator=(const Path & path)
  {
    if (this == &path)
      return *this;
    m_path = path.path();
    return *this;
  }

  bool
  Path::isset () const
  {
    return m_path.length () > 0;
  }

  void
  Path::addComponent (const QString& _component)
  {
    Pool pool;
    QString component = _component;
    while (component.endsWith('/') && component.size()>0) {
        component.chop(1);
    }
    if (Url::isValid (m_path))
    {
      const char * newPath =
#if ((SVN_VER_MAJOR == 1) && (SVN_VER_MINOR >= 6)) || (SVN_VER_MAJOR > 1)
        svn_path_url_add_component2(m_path.toUtf8(), component.toUtf8(), pool);
#else
        svn_path_url_add_component(m_path.toUtf8(), component.toUtf8(), pool);
#endif
      m_path = QString::fromUtf8(newPath);
    }
    else
    {
      svn_stringbuf_t * pathStringbuf =
          svn_stringbuf_create (m_path.toUtf8(), pool);

      svn_path_add_component (pathStringbuf,
                              component.toUtf8());

      m_path = QString::fromUtf8(pathStringbuf->data);
    }
  }


  void
  Path::addComponent (const char* component)
  {
    addComponent (QString::fromUtf8(component));
  }


  void
  Path::removeLast()
  {
    Pool pool;
    if (m_path.length()<=1) {
        m_path=QString::fromUtf8("");
    }
    svn_stringbuf_t*pathStringbuf=
            svn_stringbuf_create (m_path.toUtf8(), pool);
    svn_path_remove_component(pathStringbuf);
    m_path = QString::fromUtf8(pathStringbuf->data);
  }

  void
  Path::split (QString & dirpath, QString & basename) const
  {
    Pool pool;

    const char * cdirpath;
    const char * cbasename;

    svn_path_split (prettyPath().toUtf8(), &cdirpath, &cbasename, pool);
    dirpath = QString::fromUtf8(cdirpath);
    basename = QString::fromUtf8(cbasename);
  }


  void
  Path::split (QString & dir, QString & filename, QString & ext) const
  {
    QString basename;

    // first split path into dir and filename+ext
    split (dir, basename);

    // next search for last .
    int pos = basename.lastIndexOf(QChar('.'));

    if (pos == -1)
    {
      filename = basename;
      ext = QString::fromLatin1("");
    }
    else
    {
      filename = basename.left(pos);
      ext = basename.mid(pos+1);
    }
  }

  Path
  Path::getTempDir ()
  {
    const char * tempdir = 0;
    Pool pool;

    if (apr_temp_dir_get (&tempdir, pool) != APR_SUCCESS)
    {
      tempdir = 0;
    }

    return tempdir;
  }

    void
    Path::parsePeg(const QString&pathorurl,Path&_path,svn::Revision&_peg)
    {
        const char *truepath = 0;
        svn_opt_revision_t pegr;
        svn_error_t *error = 0;
        QByteArray _buf = pathorurl.toUtf8();

        Pool pool;
        error = svn_opt_parse_path(&pegr, &truepath,_buf,pool);
        if (error != 0) {
            throw ClientException (error);
        }
        //qDebug("Path: %s",truepath);
        _peg = svn::Revision(&pegr);
        _path=Path(truepath);
    }

  unsigned int
  Path::length () const
  {
    return m_path.length ();
  }


  QString
  Path::native () const
  {
    Pool pool;

    return QString::fromUtf8(svn_path_local_style (m_path.toUtf8(), pool));
  }

}
