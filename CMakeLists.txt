cmake_minimum_required(VERSION 3.30.4)

# Imposta il nome del progetto e la versione
project(GameProject VERSION 1.0)

# Imposta la versione di C++ da usare
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Aggiungi il percorso alle directory di include e librerie di SFML
set(SFML_DIR "C:/Users/bello/Documents/LIBS/SFML-3.0.0")
include_directories(${SFML_DIR}/include)
link_directories(${SFML_DIR}/lib)

# Aggiungi i file sorgenti del progetto (assumendo che si trovino nella cartella src)
include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Crea l'eseguibile
add_executable(${PROJECT_NAME} ${SOURCES})

# Collega le librerie SFML (usa le versioni statiche delle librerie)
target_link_libraries(${PROJECT_NAME} 
    sfml-graphics 
    sfml-window 
    sfml-system
    sfml-audio
)
