#include "llvm/Pass.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

struct TelemetryInjectorPass : public llvm::PassInfoMixin<TelemetryInjectorPass> {
    llvm::PreservedAnalyses run(llvm::Module &M, llvm::ModuleAnalysisManager &MAM){
        bool modified = false;

        for (llvm::Function &F : M) {
            if (F.isDeclaration()) {
                continue;
            }

            llvm::errs() << "[OHM Injector] Detected function: " << F.getName() << "\n";
        }

        return modified ? llvm::PreservedAnalyses::none() : llvm::PreservedAnalyses::all();
    }
};

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION, "TelemetryInjectorPass", LLVM_VERSION_STRING,
        [](llvm::PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](llvm::StringRef Name, llvm::ModulePassManager &MPM,
                   llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) {
                    if (Name == "telemetry-injector") {
                        MPM.addPass(TelemetryInjectorPass());
                        return true;
                    }
                    return false;
                });
        }
    };
}
