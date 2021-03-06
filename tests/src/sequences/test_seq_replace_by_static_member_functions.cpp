#include "sequence.hpp"
#include "gtest/gtest.h"

TEST(Sequence, replace_by_static_member_functions) {
  {
    class Test {
    public:
      int base(int a, int b) { return a + b; }

      static int &seq1(int &a) {
        a++;
        return a;
      }

      static int &seq2(int &a) {
        a += 2u;
        return a;
      }
    };

    Test test_;
    sequence_t sequence_(&test_, &Test::base);
    uint32_t sequence_error_id = static_cast<uint32_t>(seq_errno_e::SEQ_CLEAR);
    auto op = sequence_
                  .set_error_handler(
                      [&sequence_error_id](const sha256::sha256_hash_type &id, const uint32_t &error_id,
                                           const uint32_t &error_case_id = static_cast<uint32_t>(error_case_e::ERROR_CASE_RUNTIME)) -> void {
                        sequence_error_id = error_id;
                      })
                  .qualifiers.at(sequence_.get_id());

    EXPECT_EQ(op, static_cast<uint32_t>(seq_errno_e::SEQ_CLEAR));

    {
      auto add_result = sequence_.add("Seq1", Test::seq1);

      EXPECT_EQ(add_result.status.qualifiers.at(sequence_.get_id()), static_cast<uint32_t>(seq_errno_e::SEQ_CLEAR));
      EXPECT_EQ(add_result.data.first, sha256::compute(reinterpret_cast<const uint8_t *>("Seq1"), std::strlen("Seq1")));

      int result = sequence_(5u, 5u);

      EXPECT_EQ(result, 5u + 5u + 1u);
    }

    {
      auto replace_result = sequence_.replace("Seq1", "Seq2", Test::seq2);

      EXPECT_EQ(replace_result.status.qualifiers.at(sequence_.get_id()), static_cast<uint32_t>(seq_errno_e::SEQ_CLEAR));
      EXPECT_EQ(replace_result.data.first,
                sha256::compute(reinterpret_cast<const uint8_t *>("Seq2"), std::strlen("Seq2")));

      int result = sequence_(5u, 5u);

      EXPECT_EQ(result, 5u + 5u + 2u);
    }

    EXPECT_EQ(sequence_.clear().qualifiers.at(sequence_.get_id()), static_cast<uint32_t>(seq_errno_e::SEQ_CLEAR));
  }

  {
    class Test {
    public:
      int base(int a, int b) { return a + b; }

      static int &seq1(int &a) {
        a++;
        return a;
      }

      static int &seq2(int &a) {
        a += 2u;
        return a;
      }
    };

    Test test_;
    std::function<int(int, int)> base = [](int a, int b) -> int { return a + b; };
    sequence_t sequence_(base);

    uint32_t sequence_error_id = static_cast<uint32_t>(seq_errno_e::SEQ_CLEAR);
    auto op = sequence_
                  .set_error_handler(
                      [&sequence_error_id](const sha256::sha256_hash_type &id, const uint32_t &error_id,
                                           const uint32_t &error_case_id = static_cast<uint32_t>(error_case_e::ERROR_CASE_RUNTIME)) -> void {
                        sequence_error_id = error_id;
                      })
                  .qualifiers.at(sequence_.get_id());

    EXPECT_EQ(op, static_cast<uint32_t>(seq_errno_e::SEQ_CLEAR));

    {
      auto add_result = sequence_.add("Seq1", Test::seq1);

      EXPECT_EQ(add_result.status.qualifiers.at(sequence_.get_id()), static_cast<uint32_t>(seq_errno_e::SEQ_CLEAR));
      EXPECT_EQ(add_result.data.first, sha256::compute(reinterpret_cast<const uint8_t *>("Seq1"), std::strlen("Seq1")));

      int result = sequence_(5u, 5u);

      EXPECT_EQ(result, 5u + 5u + 1u);
    }

    {
      auto replace_result = sequence_.replace("Seq1", "Seq2", Test::seq2);

      EXPECT_EQ(replace_result.status.qualifiers.at(sequence_.get_id()), static_cast<uint32_t>(seq_errno_e::SEQ_CLEAR));
      EXPECT_EQ(replace_result.data.first,
                sha256::compute(reinterpret_cast<const uint8_t *>("Seq2"), std::strlen("Seq2")));

      int result = sequence_(5u, 5u);

      EXPECT_EQ(result, 5u + 5u + 2u);
    }

    sequence_.clear();
  }

  {
    class Test {
    public:
      int base(int a, int b) { return a + b; }

      static int &seq1(int &a) {
        a++;
        return a;
      }

      static int &seq2(int &a) {
        a += 2u;
        return a;
      }
    };

    Test test_;
    std::string testing_string;
    std::function<int(int, int)> base = [&testing_string](int a, int b) -> int {
      testing_string = std::to_string(a + b);
      return a + b;
    };

    sequence_t sequence_(base);

    uint32_t sequence_error_id = static_cast<uint32_t>(seq_errno_e::SEQ_CLEAR);
    auto op = sequence_
                  .set_error_handler(
                      [&sequence_error_id](const sha256::sha256_hash_type &id, const uint32_t &error_id,
                                           const uint32_t &error_case_id = static_cast<uint32_t>(error_case_e::ERROR_CASE_RUNTIME)) -> void {
                        sequence_error_id = error_id;
                      })
                  .qualifiers.at(sequence_.get_id());

    EXPECT_EQ(op, static_cast<uint32_t>(seq_errno_e::SEQ_CLEAR));

    {
      auto add_result = sequence_.add("Seq1", Test::seq1);

      EXPECT_EQ(add_result.status.qualifiers.at(sequence_.get_id()), static_cast<uint32_t>(seq_errno_e::SEQ_CLEAR));
      EXPECT_EQ(add_result.data.first, sha256::compute(reinterpret_cast<const uint8_t *>("Seq1"), std::strlen("Seq1")));

      int result = sequence_(5u, 5u);

      EXPECT_EQ(result, 5u + 5u + 1u);
      EXPECT_STREQ(testing_string.c_str(), std::to_string(5 + 5).c_str());
    }

    {
      auto replace_result = sequence_.replace("Seq1", "Seq2", Test::seq2);

      EXPECT_EQ(replace_result.status.qualifiers.at(sequence_.get_id()), static_cast<uint32_t>(seq_errno_e::SEQ_CLEAR));
      EXPECT_EQ(replace_result.data.first,
                sha256::compute(reinterpret_cast<const uint8_t *>("Seq2"), std::strlen("Seq2")));

      int result = sequence_(5u, 5u);

      EXPECT_EQ(result, 5u + 5u + 2u);
      EXPECT_STREQ(testing_string.c_str(), std::to_string(5u + 5u).c_str());
    }

    EXPECT_EQ(sequence_.clear().qualifiers.at(sequence_.get_id()), static_cast<uint32_t>(seq_errno_e::SEQ_CLEAR));
  }
}
