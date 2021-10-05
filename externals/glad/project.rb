cxx_configuration do
  sources = FileList['src/glad.c']
  static_lib(
    "glad",
    sources: sources,
    includes: ['include'],
  )
end
