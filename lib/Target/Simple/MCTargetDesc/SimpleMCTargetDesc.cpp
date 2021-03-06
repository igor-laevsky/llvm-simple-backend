#include "SimpleMCTargetDesc.h"
#include "SimpleMCAsmInfo.h"
#include "InstPrinter/SimpleInstPrinter.h"
#include "llvm/MC/MCCodeGenInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "SimpleGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "SimpleGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "SimpleGenRegisterInfo.inc"

static MCAsmInfo *createSimpleMCAsmInfo(const MCRegisterInfo &MRI,
                                       StringRef TT) 
{
  MCAsmInfo *MAI = new SimpleMCAsmInfo(TT);
  return MAI;
}

static MCInstPrinter *createSimpleMCInstPrinter(const Target &T,
                                               unsigned SyntaxVariant,
                                               const MCAsmInfo &MAI,
                                               const MCInstrInfo &MII,
                                               const MCRegisterInfo &MRI,
                                               const MCSubtargetInfo &STI) 
{
  return new SimpleInstPrinter(MAI, MII, MRI);
}

// Force static initialization.
extern "C" void LLVMInitializeSimpleTargetMC() {
  // Register the MC asm info.
  RegisterMCAsmInfoFn X(TheSimpleTarget, createSimpleMCAsmInfo);

  TargetRegistry::RegisterMCInstPrinter(TheSimpleTarget,
    createSimpleMCInstPrinter);
}
