cxx_configuration do
  static_lib(
    "sgtools-glfw",
    sources: FileList["**/*.cpp"],
    dependencies: ["sgtools", "glfw", "glad"],
    includes: [".."],
  )
end
