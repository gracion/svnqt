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
 
/*!
 * \file client_commit_parameter.h
 * \brief defining classes working as named parameters for different subversion commit
 *
 * Subversion has various functions which has growing / changing parameter lists from version to version.
 * since subversion 1.4 this changes are more and more unhandy for a c++ wrapper due every time changes to
 * virtual class. This special data containers may reduce changes of signatures to the client interface.
 */

#ifndef CLIENT_COMMIT_PARAMETER_H
#define CLIENT_COMMIT_PARAMETER_H

#include "svnqt_global.h"
#include "svnqttypes.h"
#include "revision.h"
#include "targets.h"
#include "path.h"
#include "shared_pointer.h"

namespace svn
{
    struct CommitParameterData;
    class SVNQT_EXPORT CommitParameter
    {
    private:
        SharedPointer<CommitParameterData> _data;

    public:
        CommitParameter();
        ~CommitParameter();

        //!files to commit.
        CommitParameter&targets(const Targets&targets);
        //!files to commit.
        const Targets&targets()const;
        //! log message. if QString() svnqt ask for a message
        CommitParameter&message(const QString&message);
        //! log message. if QString() svnqt ask for a message
        const QString&message()const;
        //! default empty
        CommitParameter&changeList(const StringArray&_changeList);
        //! default empty
        const StringArray&changeList()const;
        //! default empty
        CommitParameter&revisionProperties(const PropertiesMap&_revProps);
        //! default empty
        const PropertiesMap&revisionProperties()const;
        //! default DepthInfinity
        CommitParameter&depth(Depth depth);
        //! default DepthInfinity
        Depth depth()const;
        //! if false unlock items in path (default)
        CommitParameter&keepLocks(bool _keep);
        //! if false unlock items in path (default)
        bool keepLocks()const;
        //! default false
        CommitParameter&keepChangeList(bool _keep);
        //! default false
        bool keepChangeList()const;
    };
}


#endif
