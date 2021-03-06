/*
 * Copyright (c) 2002-2005 The RapidSvn Group.
 * Copyright (c) 2005-2009 by Rajko Albrecht (ral@alwins-world.de)
 * Copyright (c) 2011 Tim Besard <tim.besard@gmail.com>
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#ifndef SVNQT_WC_H
#define SVNQT_WC_H

// Ignore MSVC 7, 2005 & 2008 compiler warning: C++ exception specification
#if defined (_MSC_VER) && _MSC_VER > 1200 && _MSC_VER <= 1550
#pragma warning (disable: 4290)
#endif

// svncpp
#include "svnqt_global.h"
#include "exception.h"
#include "revision.h"
#include "svnqttypes.h"

#include <qstring.h>

namespace svn
{
  /**
   * Class that deals with a working copy
   */
  class SVNQT_EXPORT Wc
  {
  public:

    /** initialize
     * @param context the context to use for cancel operations, if 0 then no cancel operation possible
     */
    Wc(const ContextP&context);
    ~Wc();
    /**
     * check if Path is a valid working directory
     *
     * @param dir path to a directory
     * @return true=valid working copy
     */
    static bool
    checkWc (const QString& dir);

    /**
     * ensure that an administrative area exists for @a dir, so that @a dir
     * is a working copy subdir based on @a url at @a revision.
     *
     * @param dir path to a directory
     * @param uuid
     * @param url corresponding url
     * @param revision expected working copy revision
     * @param repository if not QString::null prefix of url
     * @param depth definite depth never DepthUnknown
     * @sa svn_wc_ensure_adm3 for more details
     */
    static void
    ensureAdm (const QString& dir, const QString& uuid,
               const QString& url, const Revision & revision,
               const QString&repository, Depth depth) throw (ClientException);

    /**
     * retrieve the url of a given working copy item
     * @param path the working copy item to check
     * @return the repository url of @a path
     */
    QString getUrl(const QString&path)const throw (ClientException);
    QString getRepos(const QString&path)const throw (ClientException);
    Entry getEntry(const QString &path)const throw ( ClientException );

    /**
     * @return returns the context (may 0)
     */
    const ContextP getContext () const;

    static const char * ADM_DIR_NAME;

  private:
    Wc();
    Wc(const Wc&);
    ContextP _context;
  };
}

#endif
