cxx_configuration do
  exe(
    "sghelloworld-glut",
    sources: ["main.cpp", "setupglutengine.cpp"],
    dependencies: ["sgtools-glut"],
  )
  exe(
    "sghelloworld-glfw",
    sources: ["main.cpp", "setupglfwengine.cpp"],
    dependencies: ["sgtools-glfw", "OpenGL"],
  )
end
