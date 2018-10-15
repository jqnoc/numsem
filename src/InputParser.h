//! @brief Parse C++ options
//! @author Diego Rodriguez Martinez (diego.rodriguez@usc.es)
//! Iain contributions from Stack Overflow
//! https://stackoverflow.com/questions/865668
//! http://iainhull.github.io


#include<vector>
#include<string>


#define NUM_REQUIRED_ARGS 1

class InputParser{

  struct Token {
    std::string str;
    bool opt;
  };

public:

    InputParser (int &argc, char **argv){

      if (argc > 1) {
        // Is there any argument?

        int start_point;

        // Positional arguments
        std::string str_st = std::string(argv[1]);
        if (argc > NUM_REQUIRED_ARGS and str_st.find_first_of("-") != 0) {
          this->problem = str_st;
          start_point = 2;
        }
        else {
          start_point = 1;
        }

        // Optional arguments
        for (int i=start_point; i < argc; ++i) {
          std::string str = std::string(argv[i]);
          if (str.find_first_of("-") == 0 and str.find_first_of("=") != std::string::npos) {
            // Si empieza por '-' y tiene un '=' en algún lado => descomponemos
            std::size_t pos_equal = str.find("=");
            std::string opt = str.substr (0,pos_equal);
            Token option_name;
            option_name.str = opt;
            option_name.opt = true;
            this->tokens.push_back(option_name);
            Token option_value;
            option_value.str = str.substr (pos_equal+1);
            option_value.opt = false;
            this->tokens.push_back(option_value);
          }
          else {
            Token option_name;
            option_name.str = str;
            if (str.find_first_of("-") == 0) {
              option_name.opt = true;
            } else {
              option_name.opt = false;
            }
            this->tokens.push_back(option_name);
          }
        }

        if (false) {
          std::cout << "ARGS:" << std::endl;
          for (unsigned i=0; i<this->tokens.size(); ++i) {
            std::cout << " + " << this->tokens[i].str;
            if (this->tokens[i].opt) std::cout << "*";
            std::cout << std::endl;
          }
        }
      }
    }

    bool isErrorCmd() const{
      for (unsigned i=0; i<this->tokens.size(); ++i) {
        if (this->tokens[i].str.find_first_of("=") == 0) {
          return true;
        }
      }
      return false;
    }

    const std::string getCmdArg(const std::string &option) const{

      unsigned i=0;
      while (i<this->tokens.size()) {
        if (this->tokens[i].opt) { // Solo mirarmos los que son opciones
          if (this->tokens[i].str.compare(option) == 0) {
            i++;
            if (i == this->tokens.size()) return ""; // Estamos al final
            if (this->tokens[i].opt) return ""; // No hay argumento
            return this->tokens[i].str;
          }
        }
        i++;
      }
      return "";
    }
    /// @author diego
    const std::string UnknownOptionFound(std::vector<std::string> list_of_knowns) const{
      std::string list_of_unknowns = "";
      for (unsigned i=0; i<this->tokens.size(); ++i) {
        if (this->tokens[i].opt) { // Solo miramos los que son opciones
          std::vector<std::string>::const_iterator itr;
          itr = std::find(list_of_knowns.begin(), list_of_knowns.end(), this->tokens[i].str);
          if (itr >= list_of_knowns.end()) {
            list_of_unknowns.append(this->tokens[i].str+" "); // Si no está en la lista de conocidos
          }
        }
      }
      return list_of_unknowns;
    }
    /// @author iain
    bool cmdOptionExists(const std::string &incumbent) const{
      for (unsigned i=0; i<this->tokens.size(); ++i) {
        if (this->tokens[i].opt) { // Solo miramos los que son opciones
          if (this->tokens[i].str.compare(incumbent) == 0) {
            return true;
          }
        }
      }
      return false;
    }

    bool cmdNoOptions() const {
      return this->tokens.empty();
    }

    bool cmdNoProblem() const {
      return this->problem.empty();
    }

    unsigned getOptionsSize() const {
      return this->tokens.size();
    }

    std::string getProblem() const {
      return this->problem;
    }

private:
    std::vector <Token> tokens;
    std::string problem = "";
    bool errors = false;
};
