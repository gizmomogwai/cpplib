cxx_configuration do
  flags = {
    :DEFINES => ['OSX']
  }

  sources = FileList['**/*.cpp'].delete_if do |f|
    f.index('rar') #||
    #f.index('zip')
  end

  static_lib("io",
             sources: sources,
             includes: ['..'],
             dependencies: ['lang', BinaryLibrary.new('z')],
             toolchain: Provider.modify_cpp_compiler("gcc", flags))
end
