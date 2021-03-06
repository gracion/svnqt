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
 

#ifndef SVNQT_TYPES_H
#define SVNQT_TYPES_H

#include "svnqt_global.h"
#include "shared_pointer.h"

#include <QList>
#include <QMap>
#include <QPair>

namespace svn
{
    // forward declarations
    class AnnotateLine;
    class Context;
    class DirEntry;
    class Entry;
    class InfoEntry;
    class LogEntry;
    class Revision;
    class Status;
    class Targets;
    class Path;
    class StringArray;
    class CommitItem;
    class CopyParameter;
    class DiffParameter;
    class StatusParameter;
    class LogParameter;
    class PropertiesParameter;
    class MergeParameter;
    class CheckoutParameter;
    class CommitParameter;
    class AnnotateParameter;
    class UpdateParameter;

    typedef QList<AnnotateLine> AnnotatedFile;
    typedef smart_pointer<svn::Context> ContextP;

    typedef SharedPointer<DirEntry> DirEntryPtr;
    typedef QList<DirEntryPtr> DirEntries;
    typedef QList<InfoEntry> InfoEntries;
    /// simple list of log entries
    typedef QList<LogEntry> LogEntries;
    /// shared_pointer for LogEntriesMap
    typedef SharedPointer<LogEntries> LogEntriesPtr;

    /// map of logentries - key is revision
    typedef QMap<long,LogEntry> LogEntriesMap;
    /// shared_pointer for LogEntriesMap
    typedef SharedPointer<LogEntriesMap> LogEntriesMapPtr;

    typedef SharedPointer<Status> StatusPtr;
    typedef QList<StatusPtr> StatusEntries;
    typedef QList<Revision> Revisions;

    /** Range of Revision */
    typedef QPair<Revision,Revision> RevisionRange;
    /** list of revision ranges */
    typedef QList<RevisionRange> RevisionRanges;

    /// map of property names to values
    typedef QMap<QString,QString> PropertiesMap;
    /// pair of path, PropertiesMap
    typedef QPair<QString, PropertiesMap> PathPropertiesMapEntry;
    /// vector of path, Properties pairs
    typedef QList<PathPropertiesMapEntry> PathPropertiesMapList;
    /// shared pointer for properties
    typedef SharedPointer<PathPropertiesMapList> PathPropertiesMapListPtr;

    typedef QList<Path> Pathes;

    typedef QList<CommitItem> CommitItemList;

    //! Mapper enum for svn_depth_t
    /*!
     * Until subversion prior 1.5 is supported by this lib we must hide the svn_depth_t enum from interface.
     * \since subversion 1.5 / svnqt 1.0
     * \sa svn_depth_t
     */
    enum Depth {
        DepthUnknown,
        DepthExclude,
        DepthEmpty,
        DepthFiles,
        DepthImmediates,
        DepthInfinity
    };

    //! For search specific server capabilities
    /*!
     * \since subversion 1.5
     * when build with subversion earlier 1.5 this will not used.
     * \sa svn_repos_has_capability
     */
    enum Capability {
        CapabilityMergeinfo=0,
        CapabilityDepth,
        CapabilityCommitRevProps,
        CapabilityLogRevProps
    };

    namespace repository {
        class CreateRepoParameter;
    }
}

#endif
