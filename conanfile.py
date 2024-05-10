from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
import re
import os

class airasheJsonRecipe(ConanFile):
    name = "airashe-json"
    package_type = "library"
    version = None

    # Optional metadata
    author = "airashe"
    url = "https://github.com/airashe/airashe-json"
    description = "A library to work with JSON"

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False], "include_tools": [True, False]}
    default_options = {"shared": False, "fPIC": True, "include_tools": False}

    # Exported sources
    exports_sources = "CMakeLists.txt", "src/*.cpp", "src/*.h*", "cmake/*", "tests/*.cc", "tests/CMakeLists.txt"

    # Call before everything to define version
    def init(self):
        try:
            path = os.path.join(self.recipe_folder, "CMakeLists.txt")
            with open(path, "r") as f:
                content = f.read()
                version = re.search(b"\(AIRASHEJSON_VERSION (.*)\)", content.encode()).group(1).decode()
                self.version = version
                pass
        except Exception as e:
            print(e)
            return

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        if (self.conf.get("tools.build:skip_test", default=False)):
            tc.variables["BUILD_TESTING"] = False
        if (self.options["include_tools"]):
            tc.variables["AIRASHE_INCLUDE_TOOLS"] = True
            self.exports_sources = self.exports_sources, "tools/*"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        if not self.conf.get("tools.build:skip_test", default=False):
            test_folder = os.path.join("tests")
            if self.settings.os == "Windows":
                test_folder = os.path.join("tests", str(self.settings.build_type))
            self.output.highlight("Running tests...")
            self.run(os.path.join(test_folder, "airashe-json-tests"))

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def requirements(self):
        self.test_requires("gtest/1.14.0")

    def package_info(self):
        self.cpp_info.set_property("cmake_find_mode", "none")
        self.cpp_info.builddirs.append(os.path.join("lib", "cmake", "airashe-json"))
        self.cpp_info.libs = ["airashe-json"]
