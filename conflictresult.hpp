/***************************************************************************
 *   Copyright (C) 2007 by Rajko Albrecht  ral@alwins-world.de             *
 *   http://kdesvn.alwins-world.de/                                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#ifndef _CONFLICT_RESULT_HPP
#define _CONFLICT_RESULT_HPP

struct svn_wc_conflict_result_t;

#include "svnqt/pool.hpp"
#include "svnqt/svnqt_defines.hpp"
#include <svn_types.h>

#include <qstring.h>

namespace svn {

class SVNQT_EXPORT ConflictResult
{
    public:
        enum ConflictChoice {
            //! let user make a call to resolve
            ChoosePostpone,
            ChooseBase,
            ChooseTheirsFull,
            ChooseMineFull,
            ChooseTheirsConflict,
            ChooseMineConflict,
            ChooseMerged
        };
        ConflictResult();
        //! Copy constructor
        /*! only usefull wenn build with subversion 1.5 or newer
         */
        ConflictResult(const svn_wc_conflict_result_t*);

        const QString& mergedFile()const
        {
            return m_MergedFile;
        }
        void setMergedFile(const QString&aMergedfile);

        ConflictChoice choice()const
        {
            return m_choice;
        }
        void setChoice(ConflictChoice aValue);

        const svn_wc_conflict_result_t*result(const Pool&pool)const;
        void assignResult(svn_wc_conflict_result_t**aResult,const Pool&pool)const;

    protected:
        ConflictChoice m_choice;
        //! Merged file
        /*! will only used if m_choice is ChooseMerged
         */
        QString m_MergedFile;
};

}

#endif