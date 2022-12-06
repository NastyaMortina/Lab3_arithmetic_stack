file(GLOB hdrs "*.h*") 
file(GLOB srcs "*.cpp")
add_executable(samples ${ srcs } ${ hdrs } Queue.h Stack.h Lexema.h Arithmetic.h Operations.h Exepcion.h) 