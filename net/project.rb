cxx_configuration do
  sources = FileList['**/*.cpp'].delete_if do |f|
    f.index('url/')
  end

  static_lib("net",
             sources: sources,
             dependencies: ['lang']
            )
end
