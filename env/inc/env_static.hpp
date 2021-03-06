#ifndef ENV_STATIC_HPP
#define ENV_STATIC_HPP

#include "env_base.hpp"
#include "env_utils.hpp"
#include "network_manager.hpp"
#include "port_manager.hpp"

template <env_networking_type_e, typename...> struct env_static_s : public env_base_s {};

template <env_networking_type_e nt> struct env_static_sglt_gen_s {
  template <typename Enabled = void, typename Composition, typename... Compositions>
  static struct env_static_s<nt, Composition, Compositions...> &
  env_static_inst(const std::string &name, const char (&key)[(aes_key_size_bits / 8u) + 1u],
                  const cmps_list_static_s<Composition, Compositions...> &compositions,
                  typename std::enable_if<is_secure_type(nt), Enabled>::type * = nullptr) {
    static const std::unique_ptr<env_static_s<nt, Composition, Compositions...>> inst{
        new env_static_s<nt, Composition, Compositions...>(name, key, compositions)};
    return *inst;
  }

  template <typename Enabled = void, typename Composition, typename... Compositions>
  static struct env_static_s<nt, Composition, Compositions...> &
  env_static_inst(const std::string &name, const cmps_list_static_s<Composition, Compositions...> &compositions,
                  typename std::enable_if<!is_secure_type(nt), Enabled>::type * = nullptr) {
    static const std::unique_ptr<env_static_s<nt, Composition, Compositions...>> inst{
        new env_static_s<nt, Composition, Compositions...>(name, compositions)};
    return *inst;
  }
};

template <env_networking_type_e nt, typename Composition, typename... Compositions>
struct env_static_s<nt, Composition, Compositions...> : public env_base_s {
private:
  using base_s = env_base_s;
  using this_s = env_static_s<nt, Composition, Compositions...>;

  friend struct env_static_sglt_gen_s<nt>;

  template <typename Enabled>
  friend this_s &env_static_sglt_gen_s<nt>::env_static_inst(const std::string &,
                                                            const cmps_list_static_s<Composition, Compositions...> &,
                                                            typename std::enable_if<is_secure_type(nt), Enabled>::type);

  template <typename Enabled>
  friend this_s &env_static_sglt_gen_s<nt>::env_static_inst(const std::string &,
                                                            const char (&)[(aes_key_size_bits / 8u) + 1u],
                                                            const cmps_list_static_s<Composition, Compositions...> &,
                                                            typename std::enable_if<is_secure_type(nt), Enabled>::type);

public:
  explicit env_static_s(const this_s &) = delete;
  explicit env_static_s(this_s &&) = delete;
  this_s &operator=(const this_s &) = delete;
  this_s &operator=(this_s &&) = delete;
  virtual ~env_static_s() = default;

  const nm_s<nt> &nm() const { return nm_; }

  virtual void configure(const libconfig::Setting &env_config) override{};
  virtual int32_t run(int32_t argc, char *argv[]) const override { return 0; };

private:
  /* Disabling of warning related to uninitialized reference (not critical in this scope because it will be initialized
   * later or earlier (order isn't specified) */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuninitialized"
  template <typename Enabled = void>
  explicit env_static_s(const std::string &name, const char (&key)[(aes_key_size_bits / 8u) + 1u],
                        const cmps_list_static_s<Composition, Compositions...> &compositions,
                        typename std::enable_if<is_secure_type(nt), Enabled>::type * = nullptr)
      : base_s(name), cmps_(compositions), pm_(pm_sglt_gen_s::pm_inst(this, cmps_)),
        nm_(nm_sglt_gen_s<nt>::nm_inst(key, this)) {
    cmps_.setenv(this);
  }

  template <typename Enabled = void>
  explicit env_static_s(const std::string &name, const cmps_list_static_s<Composition, Compositions...> &compositions,
                        typename std::enable_if<!is_secure_type(nt), Enabled>::type * = nullptr)
      : base_s(name), cmps_(compositions), pm_(pm_sglt_gen_s::pm_inst(this, cmps_)),
        nm_(nm_sglt_gen_s<nt>::nm_inst(this)) {
    cmps_.setenv(this);
  }
#pragma GCC diagnostic pop

  const struct nm_s<nt> &nm_;
  const struct pm_s<Composition, Compositions...> &pm_;
  const struct cmps_list_static_s<Composition, Compositions...> &cmps_;
};

#endif /* ENV_STATIC_HPP */
