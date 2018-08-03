#pragma once

/*
**  Copyright(C) 2018, StepToSky
**
**  Redistribution and use in source and binary forms, with or without
**  modification, are permitted provided that the following conditions are met:
**
**  1.Redistributions of source code must retain the above copyright notice, this
**    list of conditions and the following disclaimer.
**  2.Redistributions in binary form must reproduce the above copyright notice,
**    this list of conditions and the following disclaimer in the documentation
**    and / or other materials provided with the distribution.
**  3.Neither the name of StepToSky nor the names of its contributors
**    may be used to endorse or promote products derived from this software
**    without specific prior written permission.
**
**  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**  DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
**  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**  Contacts: www.steptosky.com
*/

#include <string>
#include <cstdint>
#include <tuple>
#include <regex>
#include "Export.h"

#ifdef _MSC_VER
#   if _MSC_VER < 1900 // (VS 2015)
#       define STS_SEMVER_NOEXCEPT 
#   else
#       define STS_SEMVER_NOEXCEPT noexcept
#   endif
#else
#   define STS_SEMVER_NOEXCEPT noexcept
#endif

namespace sts {
namespace semver {

    /**************************************************************************************************/
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /**************************************************************************************************/

    /*!
     * \details Represents Semantic Versioning
     * \details http://semver.org/
     */
    class SemVersion {

        typedef uint32_t uint;

        std::tuple<uint, uint, uint> versionsTuple() const {
            return std::make_tuple(mMajor, mMinor, mPatch);
        }

    public:

        //---------------------------------------------------------------
        // @{

        SemVersion() = default;

        SemVersion(const SemVersion &) = default;

        // note: just '= default' doesn't work in VS 2013 
        SemVersion(SemVersion && move) STS_SEMVER_NOEXCEPT
            : mMajor(move.mMajor),
              mMinor(move.mMinor),
              mPatch(move.mPatch),
              mPreRelease(std::move(move.mPreRelease)),
              mBuild(std::move(move.mBuild)) {}

        SemVersion(const uint major, const uint minor, const uint patch)
            : mMajor(major),
              mMinor(minor),
              mPatch(patch) {}

        SemVersion(const uint major, const uint minor, const uint patch,
                   const char * preRelease, const char * build)
            : mMajor(major),
              mMinor(minor),
              mPatch(patch),
              mPreRelease(preRelease),
              mBuild(build) {}

        SemVersion(const uint major, const uint minor, const uint patch,
                   const std::string & preRelease, const std::string & build)
            : mMajor(major),
              mMinor(minor),
              mPatch(patch),
              mPreRelease(preRelease),
              mBuild(build) {}

        ~SemVersion() = default;

        // @}
        //---------------------------------------------------------------
        // @{

        SemVersion & operator=(const SemVersion &) = default;

        // note: just '= default' doesn't work in VS 2013 
        SemVersion & operator=(SemVersion && move) STS_SEMVER_NOEXCEPT {
            mMajor = move.mMajor;
            mMinor = move.mMinor;
            mPatch = move.mPatch;
            mPreRelease = std::move(move.mPreRelease);
            mBuild = std::move(move.mBuild);
            return *this;
        }

        // @}
        //---------------------------------------------------------------
        // @{

        /*!
         * \details Checks whether the version is valid.
         *          Invalid version has all values as 0.
         * \note 'pre release' and 'build' strings are not used for checking.
         */
        operator bool() const {
            return mMajor != 0 || mMinor != 0 || mPatch != 0;
        }

        // @}
        //---------------------------------------------------------------
        // @{

        /*!
         * \details Compares to versions.
         * \param [in] other
         * \param [in] preRelease compare pre-release part.
         * \param [in] build compare build part.
         * \return True if the versions are equaled otherwise false.
         */
        SemVerExp bool compare(const SemVersion & other, bool preRelease = false, bool build = false) const;

        /*!
         * \note It compares only major minor and patch parts.
         * \see \link SemVersion::compare \endlink
         */
        bool operator==(const SemVersion & other) const {
            return versionsTuple() == other.versionsTuple();
        }

        /*!
         * \note It compares only major minor and patch parts.
         * \see \link SemVersion::compare \endlink
         */
        bool operator!=(const SemVersion & other) const {
            return versionsTuple() != other.versionsTuple();
        }

        /*!
         * \note It compares only major minor and patch parts.
         * \see \link SemVersion::compare \endlink
         */
        bool operator>(const SemVersion & other) const {
            return versionsTuple() > other.versionsTuple();
        }

        /*!
         * \note It compares only major minor and patch parts.
         * \see \link SemVersion::compare \endlink
         */
        bool operator<(const SemVersion & other) const {
            return versionsTuple() < other.versionsTuple();
        }

        /*!
         * \note It compares only major minor and patch parts.
         * \see \link SemVersion::compare \endlink
         */
        bool operator>=(const SemVersion & other) const {
            return versionsTuple() >= other.versionsTuple();
        }

        /*!
         * \note It compares only major minor and patch parts.
         * \see \link SemVersion::compare \endlink
         */
        bool operator<=(const SemVersion & other) const {
            return versionsTuple() <= other.versionsTuple();
        }

        // @}
        //---------------------------------------------------------------
        // @{

        /*!
         * \details Sets new values. Pre release and build values will be cleaned.
         * \param [in] major 
         * \param [in] minor 
         * \param [in] patch 
         */
        void set(const uint major, const uint minor, const uint patch) {
            mMajor = major;
            mMinor = minor;
            mPatch = patch;
            mPreRelease.clear();
            mBuild.clear();
        }

        /*!
         * \details Sets new values.
         * \param [in] major 
         * \param [in] minor 
         * \param [in] patch 
         * \param [in] preRelease 
         * \param [in] build 
         */
        void set(const uint major, const uint minor, const uint patch,
                 const char * preRelease, const char * build) {
            set(major, minor, patch);
            if (preRelease) {
                mPreRelease.append(preRelease);
            }
            if (build) {
                mBuild.append(build);
            }
        }

        /*!
         * \details Sets new values.
         * \param [in] major 
         * \param [in] minor 
         * \param [in] patch 
         * \param [in] preRelease 
         * \param [in] build 
         */
        void set(const uint major, const uint minor, const uint patch,
                 const std::string & preRelease, const std::string & build) {
            set(major, minor, patch);
            mPreRelease = preRelease;
            mBuild = build;
        }

        // @}
        //---------------------------------------------------------------
        // @{

        /*!
         * \details Parses string.
         * \param [in] version 
         * \return valid SemVersion if successful otherwise invalid.
         * \code 
         *     SemVersion ver = SemVersion::parse("string")
         *     if(ver){
         *         ... // valid
         *     }
         * \endcode
         * \link SemVersion::operator bool() const \endlink
         */
        static SemVersion parse(const char * version) {
            return version ? parse(std::string(version)) : SemVersion();
        }

        /*!
         * \details Parses string.
         * \param [in] version
         * \return valid SemVersion if successful otherwise invalid.
         * \code 
         *     SemVersion ver = SemVersion::parse("string")
         *     if(ver){
         *         ... // valid
         *     }
         * \endcode
         * \link SemVersion::operator bool() const \endlink
         */
        SemVerExp static SemVersion parse(const std::string & version);

        // @}
        //---------------------------------------------------------------
        // @{

        /*!
         * \details Makes string from the values.
         * \param [in] preRelease add 'pre release' value if true.
         * \param [in] build add 'build' value if true.
         * \return built string from the values.
         */
        SemVerExp std::string toString(bool preRelease = false, bool build = false) const;

        /*!
         * \details Clears all values.
         */
        void clear() {
            mMajor = 0;
            mMinor = 0;
            mPatch = 0;
            mPreRelease.clear();
            mBuild.clear();
        }

        // @}
        //---------------------------------------------------------------
        // @{

        uint mMajor = 0;
        uint mMinor = 0;
        uint mPatch = 0;
        std::string mPreRelease;
        std::string mBuild;

        // @}
        //---------------------------------------------------------------

    private:

        SemVerExp static const std::regex mRegex;

    };

    /**************************************************************************************************/
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /**************************************************************************************************/
}
}
