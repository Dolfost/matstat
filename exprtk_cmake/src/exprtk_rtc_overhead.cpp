/*
 **************************************************************
 *         C++ Mathematical Expression Toolkit Library        *
 *                                                            *
 * ExprTk Vector RTC Overhead Analysis                        *
 * Author: Arash Partow (1999-2024)                           *
 * URL: https://www.partow.net/programming/exprtk/index.html  *
 *                                                            *
 * Copyright notice:                                          *
 * Free use of the Mathematical Expression Toolkit Library is *
 * permitted under the guidelines and in accordance with the  *
 * most current version of the MIT License.                   *
 * https://www.opensource.org/licenses/MIT                    *
 * SPDX-License-Identifier: MIT                               *
 *                                                            *
 **************************************************************
*/


#include <cstdio>
#include <string>

#include "exprtk.hpp"


struct vector_access_rtc final : public exprtk::vector_access_runtime_check
{
   bool handle_runtime_violation(violation_context&) override
   {
      throw std::runtime_error("Runtime vector access violation.");
      return false;
   }
};

template <typename T>
void vector_rtc_overhead_analysis()
{
   typedef exprtk::expression<T> expression_t;
   typedef exprtk::parser<T>     parser_t;

   const std::string sieve_of_eratosthenes_program =
      " var sieve[10^8] := [false];                   "
      " var m := trunc(sqrt(sieve[]));                "
      "                                               "
      " sieve[0] := true;                             "
      " sieve[1] := true;                             "
      "                                               "
      " for (var i := 0; i <= m; i += 1)              "
      " {                                             "
      "    if (false == sieve[i])                     "
      "    {                                          "
      "       for (var j := i^2; j < sieve[]; j += i) "
      "       {                                       "
      "          sieve[j] := true;                    "
      "       }                                       "
      "    }                                          "
      " };                                            "
      "                                               "
      " var prime_count := sieve[] - sum(sieve);      "
      "                                               "
      " prime_count == 5761455;                       ";

   T nortc_result = T(0);
   T rtc_result   = T(0);

   double nortc_time_sec = T(0);
   double rtc_time_sec   = T(0);

   {
      expression_t expression;

      parser_t parser;
      parser.compile(sieve_of_eratosthenes_program,expression);

      exprtk::timer timer;
      timer.start();

      nortc_result = expression.value();

      timer.stop();
      nortc_time_sec = timer.time();
   }

   {
      vector_access_rtc vec_rtc;

      expression_t expression;

      parser_t parser;
      parser.register_vector_access_runtime_check(vec_rtc);
      parser.compile(sieve_of_eratosthenes_program,expression);

      exprtk::timer timer;
      timer.start();

      rtc_result = expression.value();

      timer.stop();
      rtc_time_sec = timer.time();
   }

   if (nortc_result == rtc_result)
   {
      printf("Execution - NORTC time: %5.3fsec\tRTC time: %5.3fsec\toverhead: %5.3f%%\n",
             nortc_time_sec,
             rtc_time_sec,
             std::max(0.0,100.0 * ((rtc_time_sec - nortc_time_sec)  / nortc_time_sec)));
   }
   else
      printf("ERROR - Results of NORTC and RTC runs do not match!\n");
}

int main(int argc, char* argv[])
{
   const std::size_t rounds = ((argc == 2) ? atoi(argv[1]) : 5);

   for (std::size_t i = 0; i < rounds; ++i)
   {
      vector_rtc_overhead_analysis<double>();
   }

   return 0;
}
