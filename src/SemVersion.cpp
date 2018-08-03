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

#include <sstream>
#include "sts/semver/SemVersion.h"

/**************************************************************************************************/
/////////////////////////////////////////* Static area *////////////////////////////////////////////
/**************************************************************************************************/

const std::regex sts::semver::SemVersion::mRegex = std::regex("^(0|[1-9][0-9]*)"
                                                              "\\.(0|[1-9][0-9]*)"
                                                              "\\.(0|[1-9][0-9]*)"
                                                              "(?:\\-([0-9a-z-]+[\\.0-9a-z-]*))?"
                                                              "(?:\\+([0-9a-z-]+[\\.0-9a-z-]*))?",
                                                              std::regex_constants::ECMAScript |
                                                              std::regex_constants::icase);

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

bool sts::semver::SemVersion::compare(const SemVersion & other, const bool preRelease, const bool build) const {
    if (this->operator!=(other)) {
        return false;
    }
    if (preRelease && mPreRelease != other.mPreRelease) {
        return false;
    }
    if (build && mBuild != other.mBuild) {
        return false;
    }
    return true;
}

sts::semver::SemVersion sts::semver::SemVersion::parse(const std::string & version) {
    auto match = std::smatch();
    if (!regex_match(version, match, mRegex)) {
        return SemVersion();
    }
    return SemVersion(atoi(match[1].str().c_str()),
                      atoi(match[2].str().c_str()),
                      atoi(match[3].str().c_str()),
                      match[4],
                      match[5]);
}

std::string sts::semver::SemVersion::toString(const bool preRelease, const bool build) const {
    std::ostringstream stream;
    stream << mMajor << '.' << mMinor << '.' << mPatch;
    if (preRelease && !mPreRelease.empty()) {
        stream << '-' << mPreRelease;
    }
    if (build && !mBuild.empty()) {
        stream << '+' << mBuild;
    }
    return stream.str();
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
