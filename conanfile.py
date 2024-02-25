from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMake, CMakeToolchain
from conan.errors import ConanInvalidConfiguration


class EmshRecipe(ConanFile):
    name = "emsh"
    version = "1.0"

    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "with_unit_tests": [True, False],
    }
    default_options = {"shared": False, "fPIC": True, "with_unit_tests": False}

    exports_sources = "CMakeLists.txt", "src/*", "include/*"

    def requirements(self):
        if self.options.with_unit_tests:
            self.requires("gtest/1.14.0")

    def validate(self):
        if self.settings.os == "Windows":
            raise ConanInvalidConfiguration("Windows not supported")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        if self.options.with_unit_tests:
            tc.cache_variables["BUILD_TESTS"] = True
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["emsh"]
