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
 
#ifndef DIFF_OPTIONS_HPP
#define DIFF_OPTIONS_HPP

#include "svnqt_global.h"

struct svn_diff_file_options_t;
class QStringList;

namespace svn
{
    class Pool;
    struct DiffOptionsData;
    /** c++ wrapper for svn_diffoptions_t
     *
     * This is needed until svnqt stops support for subversion prior 1.4
     */
    class SVNQT_EXPORT DiffOptions
    {
        public:
            enum IgnoreSpace {
                IgnoreSpaceNone,
                IgnoreSpaceChange,
                IgnoreSpaceAll
            };
        protected:
            DiffOptionsData* m_data;
            void init(const svn_diff_file_options_t*options);

        public:
            DiffOptions();
            /** Initialize options with values depending on options.
             * Supported types are:
             * - --ignore-space-change, -b
             * - --ignore-all-space, -w
             * - --ignore-eol-style
             * - --unified, -u (for compatibility, does nothing).
             * @sa svn_diff_file_options_parse
             */
            DiffOptions(const QStringList&options);

            /** Initialize options with values depending on options.
             * Only if build against subversion 1.4 or newer.
             */
            DiffOptions(const svn_diff_file_options_t*options);

            /** copy operator
             */
            DiffOptions(const DiffOptions&old);

            ~DiffOptions();

            svn_diff_file_options_t*options(const Pool&pool)const;
    };
}

#endif
