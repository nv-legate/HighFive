/*
 *  Copyright (c), 2017, Adrien Devresse <adrien.devresse@epfl.ch>
 *
 *  Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 *
 */
#ifndef H5FILE_HPP
#define H5FILE_HPP

#include <string>

#include "H5FileDriver.hpp"
#include "H5Object.hpp"

#include "bits/H5Annotate_traits.hpp"
#include "bits/H5Node_traits.hpp"

namespace HighFive {

///
/// \brief File class
///
class File : public Object,
             public NodeTraits<File>,
             public AnnotateTraits<File> {
 public:
    enum : int {
        /// Open flag: Read only access
        ReadOnly = 0x00,
        /// Open flag: Read Write access
        ReadWrite = 0x01,
        /// Open flag: Truncate a file if already existing
        Truncate = 0x02,
        /// Open flag: Open will fail if file already exist
        Excl = 0x04,
        /// Open flag: Open in debug mode
        Debug = 0x08,
        /// Open flag: Create non existing file
        Create = 0x10,
        /// Derived open flag: common write mode (=ReadWrite|Create|Truncate)
        Overwrite = Truncate,
        /// Derived open flag: Opens RW or exclusivelly creates
        OpenOrCreate = ReadWrite | Create
    };

    ///
    /// \brief File
    /// \param filename: filepath of the HDF5 file
    /// \param openFlags: Open mode / flags ( ReadOnly, ReadWrite)
    ///
    /// Open or create a new HDF5 file
    explicit File(const std::string& filename, int openFlags = ReadOnly,
                  const Properties& fileAccessProps = FileDriver());

    ///
    /// \brief Return the name of the file
    ///
    const std::string& getName() const;

    ///
    /// \brief flush
    ///
    /// Flushes all buffers associated with a file to disk
    ///
    void flush();

 private:
    std::string _filename;
};
}  // namespace HighFive

#include "bits/H5File_misc.hpp"

#endif  // H5FILE_HPP

