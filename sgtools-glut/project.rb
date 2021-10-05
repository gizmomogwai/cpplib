cxx_configuration do
  static_lib(
    "sgtools-glut",
    sources: FileList["**/*.cpp"],
    dependencies: ["sgtools", "GLUT", "OpenGL"],
    includes: [".."],
  )
end
