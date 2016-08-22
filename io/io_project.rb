cxx_configuration do
  flags = {
    :DEFINES => ['OSX']
  }

  sources = FileList['**/*.cpp'].delete_if do |f|
    f.index('rar') ||
    f.index('zip')
  end

  source_lib("io",
             :sources => sources,
             :includes => ['..'],
             :dependencies => ['lang'],
             :toolchain => Provider.modify_cpp_compiler("GCC", flags))
end
