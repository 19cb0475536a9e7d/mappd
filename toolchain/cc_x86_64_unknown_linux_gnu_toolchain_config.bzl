load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "ACTION_NAMES")
load(
    "@bazel_tools//tools/cpp:cc_toolchain_config_lib.bzl",
    "feature",
    "flag_group",
    "flag_set",
    "tool_path",
)

WINDOWS_PATH_FMT = "%s"

def _impl_x64_windows(ctx):
    tool_paths = [
        tool_path(
            name = "gcc",
            # path = WINDOWS_PATH_FMT % "gcc",
            path = "win_linux.bat",
        ),
        tool_path(
            name = "ld",
            path = "x86_win_linux_ar.bat",
        ),
        tool_path(
            name = "ar",
            path = "x86_win_linux_ar.bat",
        ),
        tool_path(
            name = "cpp",
            path = WINDOWS_PATH_FMT % "cpp",
        ),
        tool_path(
            name = "gcov",
            path = WINDOWS_PATH_FMT % "gcov",
        ),
        tool_path(
            name = "nm",
            path = WINDOWS_PATH_FMT % "nm",
        ),
        tool_path(
            name = "objdump",
            path = WINDOWS_PATH_FMT % "objdump",
        ),
        tool_path(
            name = "strip",
            path = WINDOWS_PATH_FMT % "strip",
        ),
    ]
    toolchain_include_directories_feature = feature(
        name = "toolchain_include_directories",
        enabled = True,
        flag_sets = [
            flag_set(
                actions = [
                    ACTION_NAMES.assemble,
                    ACTION_NAMES.preprocess_assemble,
                    ACTION_NAMES.linkstamp_compile,
                    ACTION_NAMES.c_compile,
                    ACTION_NAMES.cpp_compile,
                    ACTION_NAMES.cpp_header_parsing,
                    ACTION_NAMES.cpp_module_compile,
                    ACTION_NAMES.cpp_module_codegen,
                    ACTION_NAMES.lto_backend,
                    ACTION_NAMES.clif_match,
                ],
                flag_groups = [
                    flag_group(
                        flags = [
                            "-isystem",
                            "external/x86_64_unknown_linux_gnu/usr/include/",
                            # "-isystem",
                            # "external/x86_64_unknown_linux_gnu/usr/",
                            # "-isystem",
                            # "external/x86_64_unknown_linux_gnu/include/c++/4.8.5",
                            # "-isystem",
                            # "external/x86_64_unknown_linux_gnu/include/c++/4.8.5/x86_64-unknown-linux-gnu",
                            # "-isystem",
                            # "external/x86_64_unknown_linux_gnu/usr/bits",
                            # "-isystem",
                            # "external/arm-linux/lib/gcc/armv8l-linux-gnueabihf/7.5.0/include/",
                            # "-isystem",
                            # "external/arm-linux/lib/gcc/armv8l-linux-gnueabihf/7.5.0/include-fixed/",
                            # "-isystem",
                            # "external/arm-linux/armv8l-linux-gnueabihf/",
                            # "-isystem",
                            # "external/arm-linux/armv8l-linux-gnueabihf/libc",
                            # "-isystem",
                            # "external/arm-linux/armv8l-linux-gnueabihf/libc/usr/include/",
                            # "-isystem",
                            # "external/arm-linux/armv8l-linux-gnueabihf/include/",
                            # "-isystem",
                            # "external/arm-linux/armv8l-linux-gnueabihf/include/c++/7.5.0",
                            # "-isystem",
                            # "external/arm-linux/armv8l-linux-gnueabihf/include/c++/7.5.0/armv8l-linux-gnueabihf",
                            # "--std=gnu++17"
                        ],
                    ),
                ],
            ),
        ],
    )
    return cc_common.create_cc_toolchain_config_info(
        ctx = ctx,
        toolchain_identifier = "x64_windows-toolchain",
        host_system_name = "x86_64-unknown-windows-gnu",
        target_system_name = "i686-unknown-linux-gnu",
        target_cpu = "x86_64",
        target_libc = "unknown",
        compiler = "gcc",
        abi_version = "unknown",
        abi_libc_version = "unknown",
        tool_paths = tool_paths,
        features = [toolchain_include_directories_feature],
    )


cc_x86_64_unknown_linux_gnu_toolchain_config = rule(
    implementation = _impl_x64_windows,
    attrs = {},
    provides = [CcToolchainConfigInfo],
)