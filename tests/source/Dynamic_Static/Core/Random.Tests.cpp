
/*
================================================================================

  MIT License

  Copyright (c) 2016 Dynamic_Static

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

================================================================================
*/

#include "Dynamic_Static/Core/Random.hpp"

#include "catch.hpp"

#include <vector>

namespace Dynamic_Static
{
    namespace Tests
    {
        static constexpr int32_t MaxValue = 16;
        static constexpr int32_t MinValue = -MaxValue;
        static constexpr size_t TestCount = 1024;

        TEST_CASE("Integer values stay in range", "[Random]")
        {
            SECTION("range()")
            {
                bool inRange = true;
                for (size_t i = 0; i < TestCount; ++i) {
                    auto value = dst::Random.range(MinValue, MaxValue);
                    if (value < MinValue || MaxValue < value) {
                        inRange = false;
                        break;
                    }
                }
            }

            SECTION("index()")
            {
                bool count0GetsIndex0 = true;
                for (size_t i = 0; i < TestCount; ++i) {
                    if (dst::Random.index(0) != 0) {
                        count0GetsIndex0 = false;
                        break;
                    }
                }

                bool count1GetsIndex0 = true;
                for (size_t i = 0; i < TestCount; ++i) {
                    if (dst::Random.index(1) != 0) {
                        count1GetsIndex0 = false;
                        break;
                    }
                }

                size_t count = 8;
                bool count8InRange = true;
                for (size_t i = 0; i < TestCount; ++i) {
                    if (dst::Random.index(count) >= count) {
                        count8InRange = false;
                        break;
                    }
                }

                REQUIRE(count0GetsIndex0);
                REQUIRE(count1GetsIndex0);
                REQUIRE(count8InRange);
            }

            SECTION("die_roll()")
            {
                bool d0Rolls0 = true;
                for (size_t i = 0; i < TestCount; ++i) {
                    if (dst::Random.die_roll(0) != 0) {
                        d0Rolls0 = false;
                        break;
                    }
                }

                bool d1Rolls1 = true;
                for (size_t i = 0; i < TestCount; ++i) {
                    if (dst::Random.die_roll(1) != 1) {
                        d1Rolls1 = false;
                        break;
                    }
                }

                uint32_t dieSize = 6;
                bool d6RollsInRange = true;
                for (size_t i = 0; i < TestCount; ++i) {
                    auto roll = dst::Random.die_roll(dieSize);
                    if (roll < 1u || dieSize < roll) {
                        d6RollsInRange = false;
                        break;
                    }
                }

                REQUIRE(d0Rolls0);
                REQUIRE(d1Rolls1);
                REQUIRE(d6RollsInRange);
            }
        }

        TEST_CASE("Floating point values stay in range", "[Random]")
        {
            bool inRange = true;
            float min = MinValue;
            float max = MaxValue;
            for (size_t i = 0; i < TestCount; ++i) {
                auto value = dst::Random.range(min, max);
                if (value < min || max < value) {
                    inRange = false;
                    break;
                }
            }

            REQUIRE(inRange);
        }

        TEST_CASE("Resetting produces deterministic sequences", "[Random]")
        {
            dst::Random.reset();
            float min = MinValue;
            float max = MaxValue;
            std::vector<float> sequence(TestCount);
            for (size_t i = 0; i < TestCount; ++i) {
                sequence[i] = dst::Random.range(min, max);
            }

            dst::Random.reset();
            bool deterministic = true;
            for (size_t i = 0; i < TestCount; ++i) {
                if (dst::Random.range(min, max) != sequence[i]) {
                    deterministic = false;
                    break;
                }
            }

            REQUIRE(deterministic);
        }
    } // namespace Tests
} // namespace Dynamic_Static