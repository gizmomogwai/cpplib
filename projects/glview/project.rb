cxx_configuration do
  exe(
    "glview-glut",
    sources: FileList["*.cpp"] + ["engines/setupglutengine.cpp"],
    dependencies: ["net", "io", "sgtools-glut", "image"],
  )
  exe(
    "glview-glfw",
    sources: FileList["*.cpp"] + ["engines/setupglfwengine.cpp"],
    dependencies: ["net", "io", "sgtools-glfw", "image"],
  )
end
