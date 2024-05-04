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
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    # Exported sources
    exports_sources = "CMakeLists.txt", "src/*.cpp", "src/*.h*", "cmake/*"

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
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.set_property("cmake_find_mode", "none")
        self.cpp_info.builddirs.append(os.path.join("lib", "cmake", "airashe-json"))
        self.cpp_info.libs = ["airashe-json"]
