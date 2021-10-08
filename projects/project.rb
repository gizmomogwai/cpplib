cxx_configuration do
  Framework.new("GLUT")
  Framework.new("OpenGL")
  BinaryLibrary.new("glfw").set_dependencies(["OpenGL"])
end
