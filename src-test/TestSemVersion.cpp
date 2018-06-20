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

#include "gtest/gtest.h"
#include "sts/semver/SemVersion.h"

using namespace sts::semver;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(SemVersion, constrictor_default) {
    SemVersion v;
    ASSERT_EQ(0, v.mMajor);
    ASSERT_EQ(0, v.mMinor);
    ASSERT_EQ(0, v.mPatch);
    ASSERT_EQ(0, v.mPreRelease.length());
    ASSERT_EQ(0, v.mBuild.length());
}

TEST(SemVersion, constrictor_init_1) {
    SemVersion v(1, 2, 3);
    ASSERT_EQ(1, v.mMajor);
    ASSERT_EQ(2, v.mMinor);
    ASSERT_EQ(3, v.mPatch);
    ASSERT_EQ(0, v.mPreRelease.length());
    ASSERT_EQ(0, v.mBuild.length());
}

TEST(SemVersion, constrictor_init_2) {
    SemVersion v(1, 2, 3, "pre", "build");
    ASSERT_EQ(1, v.mMajor);
    ASSERT_EQ(2, v.mMinor);
    ASSERT_EQ(3, v.mPatch);
    ASSERT_STREQ("pre", v.mPreRelease.c_str());
    ASSERT_STREQ("build", v.mBuild.c_str());
}

TEST(SemVersion, constrictor_init_3) {
    SemVersion v(1, 2, 3, std::string("pre"), std::string("build"));
    ASSERT_EQ(1, v.mMajor);
    ASSERT_EQ(2, v.mMinor);
    ASSERT_EQ(3, v.mPatch);
    ASSERT_STREQ("pre", v.mPreRelease.c_str());
    ASSERT_STREQ("build", v.mBuild.c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(SemVersion, set_1) {
    SemVersion v(1, 2, 3, "test1", "test2");
    v.set(5, 6, 7);
    ASSERT_EQ(5, v.mMajor);
    ASSERT_EQ(6, v.mMinor);
    ASSERT_EQ(7, v.mPatch);
    ASSERT_EQ(0, v.mPreRelease.length());
    ASSERT_EQ(0, v.mBuild.length());
}

TEST(SemVersion, set_2) {
    SemVersion v(1, 2, 3, "test1", "test2");
    v.set(5, 6, 7, "test3", "test4");
    ASSERT_EQ(5, v.mMajor);
    ASSERT_EQ(6, v.mMinor);
    ASSERT_EQ(7, v.mPatch);
    ASSERT_STREQ("test3", v.mPreRelease.c_str());
    ASSERT_STREQ("test4", v.mBuild.c_str());
}

TEST(SemVersion, set_3) {
    SemVersion v(1, 2, 3, "test1", "test2");
    v.set(5, 6, 7, std::string("test3"), std::string("test4"));
    ASSERT_EQ(5, v.mMajor);
    ASSERT_EQ(6, v.mMinor);
    ASSERT_EQ(7, v.mPatch);
    ASSERT_STREQ("test3", v.mPreRelease.c_str());
    ASSERT_STREQ("test4", v.mBuild.c_str());
}

TEST(SemVersion, set_4_null) {
    SemVersion v(1, 2, 3, "test1", "test2");
    v.set(5, 6, 7, nullptr, nullptr);
    ASSERT_EQ(5, v.mMajor);
    ASSERT_EQ(6, v.mMinor);
    ASSERT_EQ(7, v.mPatch);
    ASSERT_EQ(0, v.mPreRelease.length());
    ASSERT_EQ(0, v.mBuild.length());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(SemVersion, clear) {
    SemVersion v(1, 2, 3, "test1", "test2");
    v.clear();
    ASSERT_EQ(0, v.mMajor);
    ASSERT_EQ(0, v.mMinor);
    ASSERT_EQ(0, v.mPatch);
    ASSERT_EQ(0, v.mPreRelease.length());
    ASSERT_EQ(0, v.mBuild.length());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(SemVersion, validation) {
    ASSERT_FALSE(SemVersion(0, 0, 0));
    ASSERT_FALSE(SemVersion(0, 0, 0, "test", "test"));
    ASSERT_TRUE(SemVersion(1, 0, 0));
    ASSERT_TRUE(SemVersion(0, 1, 0));
    ASSERT_TRUE(SemVersion(0, 0, 1));
    ASSERT_TRUE(SemVersion(1, 2, 3));
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(SemVersion, compare) {
    ASSERT_TRUE( SemVersion(1, 2, 3).compare(SemVersion(1, 2, 3)));
    ASSERT_FALSE(SemVersion(1, 2, 3).compare(SemVersion(4, 2, 3)));
    ASSERT_FALSE(SemVersion(1, 2, 3).compare(SemVersion(4, 5, 3)));
    ASSERT_FALSE(SemVersion(1, 2, 3).compare(SemVersion(4, 5, 6)));

    ASSERT_TRUE( SemVersion(1, 2, 3, "test1", "test2").compare(SemVersion(1, 2, 3, "test1", "test2"), true, true));

    ASSERT_TRUE( SemVersion(1, 2, 3, "test1", "test2").compare(SemVersion(1, 2, 3, "test3", "test2"), false, true));
    ASSERT_FALSE(SemVersion(1, 2, 3, "test1", "test2").compare(SemVersion(1, 2, 3, "test3", "test2"), true, true));

    ASSERT_TRUE( SemVersion(1, 2, 3, "test1", "test2").compare(SemVersion(1, 2, 3, "test1", "test4"), true, false));
    ASSERT_FALSE(SemVersion(1, 2, 3, "test1", "test2").compare(SemVersion(1, 2, 3, "test1", "test4"), true, true));
}

TEST(SemVersion, equals) {
    ASSERT_TRUE( SemVersion(1, 2, 3) == SemVersion(1, 2, 3));
    ASSERT_FALSE(SemVersion(1, 2, 3) == SemVersion(4, 2, 3));
    ASSERT_FALSE(SemVersion(1, 2, 3) == SemVersion(4, 5, 3));
    ASSERT_FALSE(SemVersion(1, 2, 3) == SemVersion(4, 5, 6));
}

TEST(SemVersion, not_equals) {
    ASSERT_FALSE(SemVersion(1, 2, 3) != SemVersion(1, 2, 3));
    ASSERT_TRUE( SemVersion(1, 2, 3) != SemVersion(4, 2, 3));
    ASSERT_TRUE( SemVersion(1, 2, 3) != SemVersion(4, 5, 3));
    ASSERT_TRUE( SemVersion(1, 2, 3) != SemVersion(4, 5, 6));
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(SemVersion, greater) {
    ASSERT_FALSE(SemVersion(10, 20, 30) > SemVersion(10, 20, 30));

    ASSERT_FALSE(SemVersion(10, 20, 30) > SemVersion(10, 20, 31));
    ASSERT_FALSE(SemVersion(10, 20, 30) > SemVersion(10, 21, 30));
    ASSERT_FALSE(SemVersion(10, 20, 30) > SemVersion(11, 20, 30));
    ASSERT_FALSE(SemVersion(10, 20, 30) > SemVersion(11, 21, 31));

    ASSERT_TRUE( SemVersion(10, 20, 30) > SemVersion(10, 20, 29));
    ASSERT_TRUE( SemVersion(10, 20, 30) > SemVersion(10, 19, 30));
    ASSERT_TRUE( SemVersion(10, 20, 30) > SemVersion( 9, 20, 30));
    ASSERT_TRUE( SemVersion(10, 20, 30) > SemVersion( 9, 19, 29));
}

TEST(SemVersion, lower) {
    ASSERT_FALSE(SemVersion(10, 20, 30) < SemVersion(10, 20, 30));

    ASSERT_TRUE(SemVersion(10, 20, 30) < SemVersion(10, 20, 31));
    ASSERT_TRUE(SemVersion(10, 20, 30) < SemVersion(10, 21, 30));
    ASSERT_TRUE(SemVersion(10, 20, 30) < SemVersion(11, 20, 30));
    ASSERT_TRUE(SemVersion(10, 20, 30) < SemVersion(11, 21, 31));

    ASSERT_FALSE(SemVersion(10, 20, 30) < SemVersion(10, 20, 29));
    ASSERT_FALSE(SemVersion(10, 20, 30) < SemVersion(10, 19, 30));
    ASSERT_FALSE(SemVersion(10, 20, 30) < SemVersion(9, 20, 30));
    ASSERT_FALSE(SemVersion(10, 20, 30) < SemVersion(9, 19, 29));
}

TEST(SemVersion, greater_or_equals) {
    ASSERT_TRUE(SemVersion(10, 20, 30) >= SemVersion(10, 20, 30));

    ASSERT_FALSE(SemVersion(10, 20, 30) >= SemVersion(10, 20, 31));
    ASSERT_FALSE(SemVersion(10, 20, 30) >= SemVersion(10, 21, 30));
    ASSERT_FALSE(SemVersion(10, 20, 30) >= SemVersion(11, 20, 30));
    ASSERT_FALSE(SemVersion(10, 20, 30) >= SemVersion(11, 21, 31));

    ASSERT_TRUE(SemVersion(10, 20, 30) >= SemVersion(10, 20, 29));
    ASSERT_TRUE(SemVersion(10, 20, 30) >= SemVersion(10, 19, 30));
    ASSERT_TRUE(SemVersion(10, 20, 30) >= SemVersion(9, 20, 30));
    ASSERT_TRUE(SemVersion(10, 20, 30) >= SemVersion(9, 19, 29));
}

TEST(SemVersion, lower_or_equals) {
    ASSERT_TRUE(SemVersion(10, 20, 30) <= SemVersion(10, 20, 30));

    ASSERT_TRUE(SemVersion(10, 20, 30) <= SemVersion(10, 20, 31));
    ASSERT_TRUE(SemVersion(10, 20, 30) <= SemVersion(10, 21, 30));
    ASSERT_TRUE(SemVersion(10, 20, 30) <= SemVersion(11, 20, 30));
    ASSERT_TRUE(SemVersion(10, 20, 30) <= SemVersion(11, 21, 31));

    ASSERT_FALSE(SemVersion(10, 20, 30) <= SemVersion(10, 20, 29));
    ASSERT_FALSE(SemVersion(10, 20, 30) <= SemVersion(10, 19, 30));
    ASSERT_FALSE(SemVersion(10, 20, 30) <= SemVersion(9, 20, 30));
    ASSERT_FALSE(SemVersion(10, 20, 30) <= SemVersion(9, 19, 29));
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(SemVersion, parse_1) {
    SemVersion v(1, 2, 3, "test1", "test2");
    ASSERT_NO_THROW(ASSERT_FALSE(v.parse(nullptr)));
    ASSERT_EQ(0, v.mMajor);
    ASSERT_EQ(0, v.mMinor);
    ASSERT_EQ(0, v.mPatch);
    ASSERT_EQ(0, v.mPreRelease.length());
    ASSERT_EQ(0, v.mBuild.length());
}

TEST(SemVersion, parse_2) {
    SemVersion v;
    ASSERT_NO_THROW(ASSERT_TRUE(v.parse("1.2.3-test1+test2")));
    ASSERT_EQ(1, v.mMajor);
    ASSERT_EQ(2, v.mMinor);
    ASSERT_EQ(3, v.mPatch);
    ASSERT_STREQ("test1", v.mPreRelease.c_str());
    ASSERT_STREQ("test2", v.mBuild.c_str());
}

TEST(SemVersion, parse_3) {
    SemVersion v;
    ASSERT_NO_THROW(ASSERT_TRUE(v.parse("1.2.3-test1")));
    ASSERT_EQ(1, v.mMajor);
    ASSERT_EQ(2, v.mMinor);
    ASSERT_EQ(3, v.mPatch);
    ASSERT_STREQ("test1", v.mPreRelease.c_str());
    ASSERT_EQ(0, v.mBuild.length());
}

TEST(SemVersion, parse_4) {
    SemVersion v;
    ASSERT_NO_THROW(ASSERT_TRUE(v.parse("1.2.3")));
    ASSERT_EQ(1, v.mMajor);
    ASSERT_EQ(2, v.mMinor);
    ASSERT_EQ(3, v.mPatch);
    ASSERT_EQ(0, v.mPreRelease.length());
    ASSERT_EQ(0, v.mBuild.length());
}

TEST(SemVersion, parse_5) {
    SemVersion v;
    ASSERT_NO_THROW(ASSERT_TRUE(v.parse("1.2.3-test1.test1+test2.test2")));
    ASSERT_EQ(1, v.mMajor);
    ASSERT_EQ(2, v.mMinor);
    ASSERT_EQ(3, v.mPatch);
    ASSERT_STREQ("test1.test1", v.mPreRelease.c_str());
    ASSERT_STREQ("test2.test2", v.mBuild.c_str());
}

TEST(SemVersion, parse_6) {
    SemVersion v;
    ASSERT_NO_THROW(ASSERT_FALSE(v.parse("1.2.3-+")));
    ASSERT_EQ(0, v.mMajor);
    ASSERT_EQ(0, v.mMinor);
    ASSERT_EQ(0, v.mPatch);
    ASSERT_EQ(0, v.mPreRelease.length());
    ASSERT_EQ(0, v.mBuild.length());
}

//-------------------------------------------------------------------------

TEST(SemVersion, parse_7) {
    SemVersion v;
    ASSERT_NO_THROW(ASSERT_FALSE(v.parse("1.2.3-[test1]+[test2]")));
    ASSERT_EQ(0, v.mMajor);
    ASSERT_EQ(0, v.mMinor);
    ASSERT_EQ(0, v.mPatch);
    ASSERT_EQ(0, v.mPreRelease.length());
    ASSERT_EQ(0, v.mBuild.length());
}

TEST(SemVersion, parse_8) {
    SemVersion v;
    ASSERT_NO_THROW(ASSERT_FALSE(v.parse("1.2.3-[ test1 ]+[ test2 ]")));
    ASSERT_EQ(0, v.mMajor);
    ASSERT_EQ(0, v.mMinor);
    ASSERT_EQ(0, v.mPatch);
    ASSERT_EQ(0, v.mPreRelease.length());
    ASSERT_EQ(0, v.mBuild.length());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

TEST(SemVersion, toString_case1) {
    auto res = SemVersion(1, 2, 3, "test1", "test2").toString();
    ASSERT_STREQ("1.2.3", res.c_str());
}

TEST(SemVersion, toString_case2) {
    auto res = SemVersion(1, 2, 3, "test1", "test2").toString(false, true);
    ASSERT_STREQ("1.2.3+test2", res.c_str());
}

TEST(SemVersion, toString_case3) {
    auto res = SemVersion(1, 2, 3, "test1", "test2").toString(false, false);
    ASSERT_STREQ("1.2.3", res.c_str());
}

TEST(SemVersion, toString_case4) {
    auto res = SemVersion(1, 2, 3, "test1", "test2").toString(true, false);
    ASSERT_STREQ("1.2.3-test1", res.c_str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
