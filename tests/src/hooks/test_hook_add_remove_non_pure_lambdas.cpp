#include "hook.hpp"
#include "gtest/gtest.h"

TEST(Hook, add_remove_non_pure_lambdas) {
  {
    hook_t<void(int, int)> hook_;
    std::string captured_string;
    sha256::sha256_hash_type connected_id;

    auto func = [&captured_string](int a, int b) -> void {
      captured_string += "Summa = " + std::to_string(a + b) + " ";
    };

    uint32_t hook_error_id = static_cast<uint32_t>(hook_errno_e::HOOK_CLEAR);
    auto op = hook_
                  .set_error_handler(
                      [&hook_error_id](const sha256::sha256_hash_type &id, const uint32_t &error_id,
                                       const uint32_t &error_case_id = static_cast<uint32_t>(
                                           error_case_e::ERROR_CASE_RUNTIME)) -> void { hook_error_id = error_id; })
                  .qualifiers.at(hook_.get_id());

    EXPECT_EQ(op, static_cast<uint32_t>(hook_errno_e::HOOK_CLEAR));

    {
      auto add_result = hook_.add("Summa", func);

      EXPECT_EQ(add_result.status.qualifiers.at(hook_.get_id()), static_cast<uint32_t>(hook_errno_e::HOOK_CLEAR));
      EXPECT_EQ(add_result.data.first,
                sha256::compute(reinterpret_cast<const uint8_t *>("Summa"), std::strlen("Summa")));

      hook_(5, 5);

      EXPECT_STREQ(captured_string.c_str(), "Summa = 10 ");

      connected_id = add_result.data.first;
      captured_string.clear();
    }

    {
      auto remove_result = hook_.remove("Summa");

      EXPECT_EQ(remove_result.status.qualifiers.at(hook_.get_id()), static_cast<uint32_t>(hook_errno_e::HOOK_CLEAR));
      EXPECT_EQ(remove_result.data.first,
                sha256::compute(reinterpret_cast<const uint8_t *>("Summa"), std::strlen("Summa")));
      EXPECT_EQ(remove_result.data.first, connected_id);
      EXPECT_EQ(remove_result.data.second, 0u);
    }

    {
      auto remove_result = hook_.remove("Summa");

      EXPECT_EQ(remove_result.status.qualifiers.at(hook_.get_id()), static_cast<uint32_t>(hook_errno_e::HOOK_MISSING));
      EXPECT_EQ(remove_result.data.first,
                sha256::compute(reinterpret_cast<const uint8_t *>("Summa"), std::strlen("Summa")));
      EXPECT_EQ(remove_result.data.first, connected_id);
    }

    EXPECT_EQ(hook_.clear().qualifiers.at(hook_.get_id()), static_cast<uint32_t>(hook_errno_e::HOOK_CLEAR));
  }

  {
    hook_t<void(int, int)> hook_;
    std::string captured_string;
    sha256::sha256_hash_type connected_id;

    auto func = [&captured_string](int a, int b) -> void {
      captured_string += "Summa = " + std::to_string(a + b) + " ";
    };

    uint32_t hook_error_id = static_cast<uint32_t>(hook_errno_e::HOOK_CLEAR);
    auto op = hook_
                  .set_error_handler(
                      [&hook_error_id](const sha256::sha256_hash_type &id, const uint32_t &error_id,
                                       const uint32_t &error_case_id = static_cast<uint32_t>(
                                           error_case_e::ERROR_CASE_RUNTIME)) -> void { hook_error_id = error_id; })
                  .qualifiers.at(hook_.get_id());

    EXPECT_EQ(op, static_cast<uint32_t>(hook_errno_e::HOOK_CLEAR));

    {
      auto add_result = hook_.add("Summa", func);

      EXPECT_EQ(add_result.status.qualifiers.at(hook_.get_id()), static_cast<uint32_t>(hook_errno_e::HOOK_CLEAR));
      EXPECT_EQ(add_result.data.first,
                sha256::compute(reinterpret_cast<const uint8_t *>("Summa"), std::strlen("Summa")));

      hook_(5, 5);

      EXPECT_STREQ(captured_string.c_str(), "Summa = 10 ");

      captured_string.clear();
      connected_id = add_result.data.first;
    }

    {
      auto add_result = hook_.add("Summa", func);

      EXPECT_EQ(add_result.status.qualifiers.at(hook_.get_id()), static_cast<uint32_t>(hook_errno_e::HOOK_EXISTS));
      EXPECT_EQ(add_result.data.first,
                sha256::compute(reinterpret_cast<const uint8_t *>("Summa"), std::strlen("Summa")));

      hook_(5, 5);

      EXPECT_STREQ(captured_string.c_str(), "Summa = 10 ");
      captured_string.clear();
    }

    EXPECT_EQ(hook_.clear().qualifiers.at(hook_.get_id()), static_cast<uint32_t>(hook_errno_e::HOOK_CLEAR));
  }

  {
    hook_t<void(int, int)> hook_;
    std::string captured_string;
    sha256::sha256_hash_type connected_id;

    auto func = [&captured_string](int a, int b) -> void {
      captured_string += "Summa = " + std::to_string(a + b) + " ";
    };

    uint32_t hook_error_id = static_cast<uint32_t>(hook_errno_e::HOOK_CLEAR);
    auto op = hook_
                  .set_error_handler(
                      [&hook_error_id](const sha256::sha256_hash_type &id, const uint32_t &error_id,
                                       const uint32_t &error_case_id = static_cast<uint32_t>(
                                           error_case_e::ERROR_CASE_RUNTIME)) -> void { hook_error_id = error_id; })
                  .qualifiers.at(hook_.get_id());

    EXPECT_EQ(op, static_cast<uint32_t>(hook_errno_e::HOOK_CLEAR));

    {
      auto add_result = hook_.add("Summa", func);

      EXPECT_EQ(add_result.status.qualifiers.at(hook_.get_id()), static_cast<uint32_t>(hook_errno_e::HOOK_CLEAR));
      EXPECT_EQ(add_result.data.first,
                sha256::compute(reinterpret_cast<const uint8_t *>("Summa"), std::strlen("Summa")));

      hook_(5, 5);

      EXPECT_STREQ(captured_string.c_str(), "Summa = 10 ");
      captured_string.clear();
    }

    {
      auto add_result = hook_.add("Summa_new", func);

      EXPECT_EQ(add_result.status.qualifiers.at(hook_.get_id()), static_cast<uint32_t>(hook_errno_e::HOOK_CLEAR));
      EXPECT_EQ(add_result.data.first,
                sha256::compute(reinterpret_cast<const uint8_t *>("Summa_new"), std::strlen("Summa_new")));

      hook_(5, 5);

      EXPECT_STREQ(captured_string.c_str(), "Summa = 10 Summa = 10 ");
      captured_string.clear();
    }

    EXPECT_EQ(hook_.clear().qualifiers.at(hook_.get_id()), static_cast<uint32_t>(hook_errno_e::HOOK_CLEAR));
  }
}
