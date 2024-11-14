## Dependencies {#dependencies}

---

As it is a game engine, Techstorm has alot of dependencies and can be found within the conanfile.txt in the same folder as the main CMakeLists.txt file. In addition to this, the current dependencies are listed as listed below with it's basic purpose. 

* Jolt Physics
	* Handle Techstorm's physics. 
	* [Online Documentation](https://jrouwe.github.io/JoltPhysics/index.html)
	* [Github](https://github.com/jrouwe/JoltPhysics/tree/master)
* Libconfig
	* Handle configuration file read/write.
	* [Online Documentation](http://hyperrealm.github.io/libconfig/libconfig_manual.html)
	* [Github](https://github.com/hyperrealm/libconfig)
	* [Website](http://hyperrealm.github.io/libconfig/)
* RmlUi
	* Handle Techstorm's UI with HTML/CSS.
	* [Online Documentation](https://mikke89.github.io/RmlUiDoc/)
	* [Github](https://github.com/mikke89/RmlUi)
* Asio
	* Provides Techstorm's networking functionality
	* [Online Documentation](https://think-async.com/Asio/asio-1.30.2/doc/)
	* [Website](https://think-async.com/Asio/)
* Argh
	* Command line parsing library that is mainly used by tools. 
	* [Online Documentation](https://github.com/adishavit/argh/blob/master/README.md)
	* [Github](https://github.com/adishavit/argh)
* Dear ImGUI
	* Provides an in-game debug UI for developers.
	* [Online Documentation](https://github.com/ocornut/imgui/wiki)
	* [Github](https://github.com/ocornut/imgui)
* Sol2
	* Provides Lua scripting and modding support.
	* [Online Documentation](https://sol2.readthedocs.io/en/latest/)
	* [Github](https://github.com/ThePhD/sol2)
* Angel Script
	* Provides a more advanced form of modding and scripting support.
	* [Online Documentation](https://www.angelcode.com/angelscript/documentation.html)
	* [Website](https://www.angelcode.com/angelscript/)

If you want an indepth explanation of these dependencies and their implementation status, see \ref detailed-analysis-of-dependencies. 

## Code Conventions {#code-conventions}

---

Techstorm tries to be as easy to read as possible by making the code read similarly to English. In addition, Techstorm tries to be intuitive and understandable at a quick glance, hence it uses PascalCase and CamelCase. As such, the code conventions are simple, as outlined below. 

Before you look at the conventions, look at the below key. 

### Key {#key}

---

| Case     | Meaning                                                                                              |
| -------- | ---------------------------------------------------------------------------------------------------- |
| N/A      | Not applicable                                                                                       |
| *        | Refers to anything depending on the whitespace.                                                      |
| Cap      | Capitalized. If in both the prefix **and** suffix, that means the entire thing should be capitalized |
| Cap 1st  | First character is capitalized.                                                                      |
| ^        | Same as the above                                                                                    |
| See info | See "Other Info"                                                                                     |
| Low      | Lower case. If in both the prefix **and** suffix, that means the entire thing should be lowercase.   |
| Low 1st  | First character is lowercase                                                                         |

### Variables {#variables}

---

| Case                | Prefix  | Suffix | Other info                                               |
| ------------------- | ------- | ------ | -------------------------------------------------------- |
| Private Variables   | m*      | N/A    |                                                          |
| Protected Variables | ^       | ^      |                                                          |
| Static Variables    | s       | ^      |                                                          |
| Constant Variable   | c       | ^      |                                                          |
| Constant Global     | Cap     | Cap    | For this case, it will follow snake case **in all caps** |
| Macro               | ^       | ^      | ^                                                        |
| local variable      | low 1st | N/A    | camelCase                                                |
| Parameter variable  | ^       | ^      | ^                                                        |

> [!NOTE] Definition of a Constant Global
> A constant global is a variable that is not part of any type. For example, a macro.

### Functions {#functions}

---

Functions are simple, any that are not bound to a specific object will have the first letter lowercase. If it is a static, namespace, or global function, then it will have the first letter capitalized instead. When it comes to Preprocessor functions, it will follow the same rules as Constant Global variables, as seen below:

>  | Constant Global     | Cap     | Cap    | For this case, it will follow snake case **in all caps** |
