cxx_configuration do
  exe(
    "aview",
    sources: ["main.cpp"],
    dependencies: ["image", "util"],
  )
end