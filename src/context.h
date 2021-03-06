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
 
#ifndef SVNQT_CONTEXT_H
#define SVNQT_CONTEXT_H

#include "svnqttypes.h"

// qt
#include <qstring.h>

// Subversion api
#include "svnqt_global.h"
#include <subversion-1/svn_client.h>

// svncpp
#include "pool.h"
#include "smart_pointer.h"

namespace svn
{
  // forward declarations
  class ContextListener;
  class ContextData;

  /**
   * This class will hold the client context
   * and replace the old notification and baton
   * stuff
   */
  class SVNQT_EXPORT Context:public ref_count
  {
  public:
    /**
     * default constructor
     *
     * @param configDir location where the
     *                  subversion api stores its
     *                  configuration
     */
    Context (const QString & configDir=QString());

    /**
     * copy constructor
     *
     * @param src
     */
    Context (const Context &src);

    /**
     * destructor
     */
    virtual ~Context ();

    /**
     * enable/disable authentication caching
     *
     * @param value true=enable/false=disable
     */
    void setAuthCache (bool value);

    /**
     * set username/password for authentication
     */
    void setLogin (const QString& username, const QString& password);

    /**
     * operator to get svn_client_ctx object
     */
    operator svn_client_ctx_t * ()const;

    /**
     * return the svn_client_ctx object
     */
    svn_client_ctx_t * ctx ()const;

    /**
     * this will be called at the beginning of an action.
     * the log message will be reset.
     */
    void reset ();

    /**
     * set log message
     *
     * @param msg
     */
    void setLogMessage (const QString& msg);

    /**
     * get log message
     *
     * @return log message
     */
    const QString&
    getLogMessage () const;

    /**
     * get username
     *
     * @return username
     */
    const QString&
    getUsername () const;

    /**
     * get password
     *
     * @return password
     */
    const QString&
    getPassword () const;

    /**
     * set the listener for the context. The listener will be
     * called to poll authentication information and other
     * information like this
     *
     * @param listener
     */
    void
    setListener (ContextListener * listener);

    /**
     * get the listener
     *
     * @return the listener
     */
    ContextListener *
    getListener () const;

    /** Callback for generating list entries
     * This base implementation just adds items to @a entries. This may used for special listener like the one from KIO
     * where items may displayed direkt on call and not stored into @a entries.
     * @param entries default target list
     * @param dirent entry to add (send by subversion)
     * @param lock accociated lock (may be null!)
     * @param path the path of the item
     * @return true if inserted/displayd, false if dirent or entries aren't valid.
     */
    virtual bool contextAddListItem(DirEntries*entries, const svn_dirent_t*dirent,const svn_lock_t*lock,const QString&path);

  private:
    ContextData * m;

    /**
     * disable assignment operator
     */
    Context & operator = (const Context &);
  };
}

#endif
