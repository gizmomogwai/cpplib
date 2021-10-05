require 'cxx'

c_flags = {
  FLAGS: [
    "-Ofast",
    "-g",
    "-Wall", "-Wno-deprecated-declarations",
    "-DOPENEXIF_NO_IJG",
    "-fsanitize=address",
    "-fno-omit-frame-pointer",
  ],
}

cpp_flags = {
  FLAGS: [
    "-std=c++11",
    "-Ofast",
    "-g",
    "-Wall", "-Wno-deprecated-declarations",
    "-DOPENEXIF_NO_IJG",
    "-fsanitize=address",
    "-fno-omit-frame-pointer",
  ],
}

cxx(Dir["**/project.rb"], "out", "gcc", "./") do |tc|
  tc[:COMPILER][:C].update(c_flags)
  tc[:COMPILER][:CPP].update(cpp_flags)
  tc[:LINKER].update(cpp_flags)
  # tc[:TARGET_OS] = :UNIX | OSX | :WINDOWS
end

