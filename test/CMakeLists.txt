file(GLOB hdrs "*.h*") #Äîáàâëÿåì â ïåðåìåííóþ hdrs âñå ôàéëû ñ ðàñøèðåíèåì.h
file(GLOB srcs "*.cpp")#Äîáàâëÿåì â ïåðåìåííóþ srcs âñå ôàéëû ñ ðàñøèðåíèåì.h

add_executable(test ${ srcs } ${ hdrs }) #Ñîçäàåì ïðîåêò ñ èìåíåì test â íåãî äîáàâëÿþòñÿ ôàéëû èç ïåðåìåííûõ ${ srcs }, ${ hdrs }
target_include_directories(test PUBLIC .. / gtest)
target_link_libraries(test gtest)
include_directories(.. / samples)
