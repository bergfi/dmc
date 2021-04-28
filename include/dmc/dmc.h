template<typename Storage, template <typename, typename,template<typename,typename> typename> typename ModelChecker, typename Printer = llmc::statespace::VoidPrinter>
class DMC {
public:
    using MC = ModelChecker<VModel < llmc::storage::StorageInterface>, Storage, Printer >;
public:
    void setup(Settings& settings) {

        std::ofstream f;
        f.open("out.dot", std::fstream::trunc);

        VModel <llmc::storage::StorageInterface>* model = nullptr;
        std::string modelName = settings["model"].asString();
        if(!modelName.empty()) {
            dlerror();
            auto handle = dlopen(modelName.c_str(), RTLD_NOW);
            if(char* err = dlerror()) {
                printf("Error opening model %s: %s\n", modelName.c_str(), err);
                return;
            }

            VModel < llmc::storage::StorageInterface >
            *(*func)() = (VModel <llmc::storage::StorageInterface>* (*)()) dlsym(handle, "getModel");
            if(char* err = dlerror()) {
                printf("Error locating getModel() in model %s: %s\n", modelName.c_str(), err);
                return;
            }
            model = func();
        } else {
            std::cout << "Wrong or no model selected: " << modelName << std::endl;
        }
        if(model) {
            Printer <MC, VModel<llmc::storage::StorageInterface>> printer(f);
            _mc = new MC(model, printer);
            _mc->getStorage().setSettings(settings);
            _mc->setSettings(settings);
        }
    }

    void run() {
        _mc->go();
    }
private:
    MC* _mc;
};