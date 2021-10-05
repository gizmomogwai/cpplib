cxx_configuration do
  exe(
    "gladdemo",
    sources: ["main.cpp"],
    dependencies: ["glad", "glfw"],
  )
end
