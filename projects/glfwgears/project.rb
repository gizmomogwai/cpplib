cxx_configuration do
  exe(
    "glfwglgears",
    sources: FileList["gears.c"],
    dependencies: ["glfw", "glad"]
  )
end
