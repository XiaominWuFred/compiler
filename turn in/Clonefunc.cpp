//===- Clonefunc.cpp ----------------===//
//author: Xiaomin Wu
//ENEE 645 project
//Clone called Function, checnk return method
//to optimize return speed
//===---------------------------------===//

#define DEBUG_TYPE "clonefunc"
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/GlobalVariable.h>
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/Transforms/Utils/ValueMapper.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/SymbolTableListTraits.h"
#include "llvm/ADT/StringRef.h"

using namespace llvm;

namespace {
struct Clonefunc :  public ModulePass
{
        /** Constructor. */
	static char ID;                           
	Clonefunc() : ModulePass(ID) {}

	virtual bool runOnModule(Module &mod){
	errs()<<"Module begin: "<<'\n';
	//Create global variable 
	LLVMContext &ctx = getGlobalContext();

	 GlobalVariable* gvar_int32_gloVariable = new GlobalVariable(/*Module=*/mod, 
 	/*Type=*/IntegerType::get(ctx, 32),
 	/*isConstant=*/false,
 	/*Linkage=*/GlobalValue::CommonLinkage,
 	/*Initializer=*/0, // has initializer, specified below
 	/*Name=*/"wg4");
 	gvar_int32_gloVariable->setAlignment(4);
 
 	// Constant Definitions
 	ConstantInt* const_int32_2 = ConstantInt::get(ctx, APInt(32, StringRef("0"), 10));
  	// Global Variable Definitions
 	gvar_int32_gloVariable->setInitializer(const_int32_2);
	//Global variable end

	//Cloned function ptr
	Function **clonedFs;
	int clonedAmt;
	ValueToValueMapTy VMap;
	
	Module::FunctionListType &f = mod.getFunctionList();
	//store before return
	Function* i = (&f)->begin();
	Function* e = (&f)->end();
	
//first functions traversing, find 'p' func and clone it
	clonedAmt = 0;
	while(i != NULL){
		StringRef Fname = (*(i)).getName();
		errs() << Fname << '\n';
		StringRef::iterator stri = Fname.begin();
		
		if((*stri == 'p')&&(!Fname.equals("printf"))&&(!Fname.equals("pop_direct_branch"))){
			clonedAmt++;
			errs() << "CloneAmount count" << '\n';
		}
		i = i->getNextNode();
	}
	
	clonedFs = (Function**)malloc(clonedAmt*sizeof(Function*));	
	
	i = (&f)->begin();
	e = (&f)->end();
	while(i != NULL){
		StringRef Fname = (*(i)).getName();
		errs() << Fname << '\n';
		StringRef::iterator stri = Fname.begin();
		
		if((*stri == 'p')&&(!Fname.equals("printf"))&&(!Fname.equals("pop_direct_branch"))){
			
			errs() << "Function cloned" << '\n';
			*clonedFs = llvm::CloneFunction(i, VMap,NULL);
			
			errs() <<"cloned func name "<< (**clonedFs).getName() <<'\n';
			clonedFs++;
		}
		i = i->getNextNode();
	}

	errs()<<"STAGE 1 pass"<<'\n';

//Second, find all 'p' cloned func and replacing it's return method, add return method
	while(clonedAmt--){
		StringRef Fname = (**(--clonedFs)).getName();
		errs() << Fname << '\n';
		char* s = "_clone";
		StringRef newName = Twine(Fname,s).str();
		(**clonedFs).setName(newName);
		Fname = (**clonedFs).getName();
		errs() << Fname << '\n';
		
		//add cloned func to funclist
		f.push_back((*clonedFs));
		//errs()<<"CATCH"<<'\n';		
		Function::BasicBlockListType &bList = (*clonedFs)->getBasicBlockList();
		BasicBlock* block = (&bList)->begin();
		BasicBlock* blocke = (&bList)->end();
		while(block != blocke){
			
			BasicBlock::InstListType &inslist = block->getInstList();
			Instruction* ins = (&inslist)->begin();
			Instruction* inse = (&inslist)->end();
			
			while(ins != inse){
				
				if (isa<ReturnInst>(ins)){
					errs() << "Met Return Instruction" << '\n';
					
					if(cast<ReturnInst>(ins)->getReturnValue() != NULL){
						Value * Va = ins->getOperand(0);
						StoreInst* storeGlo = new StoreInst(Va, gvar_int32_gloVariable, block);
						storeGlo->setAlignment(4);
						storeGlo->removeFromParent();
						storeGlo->insertBefore(ins);
						errs() <<"Return value got"<< '\n';
					}else{errs()<<"VOID function"<<'\n';}
					
					//add return call
					Function* callBack = mod.getFunction("pop_direct_branch");
					if(callBack != NULL){
						CallInst* reCall = CallInst::Create(callBack, "", block);
						reCall->setCallingConv(CallingConv::C);
  						reCall->setTailCall(false);
 					 	AttributeSet reCall_PAL;
  						reCall->setAttributes(reCall_PAL);
						reCall->removeFromParent();
						reCall->insertBefore(ins);
					}else{
						errs()<<"NO pop_direct_branch func found"<<'\n';
					}
					
						
				}
				ins = ins->getNextNode();
			}
			
			block = block->getNextNode();
		}
		
		
	}	
	//end

	errs()<<"STAGE 2 pass"<<'\n';


//third functions traversing, find call site, retrieve global after call, replace called func with cloned func
	i = (&f)->begin();
	e = (&f)->end();
	while(i != NULL){
		StringRef Fname = (*(i)).getName();
		errs() << Fname << '\n';
		char* s = "_clone";
		StringRef checkName = Twine(Fname,s).str();
		Function* checkHandle = mod.getFunction(checkName);
		//ignore 
		if(checkHandle == NULL){
			if(!Fname.equals("pop_direct_branch")){
				Function::BasicBlockListType &bList = i->getBasicBlockList();
				BasicBlock* block = (&bList)->begin();
				BasicBlock* blocke = (&bList)->end();
				while(block != blocke){
					BasicBlock::InstListType &inslist = block->getInstList();
					Instruction* ins = (&inslist)->begin();
					Instruction* inse = (&inslist)->end();
					while(ins != inse){
						
						if (isa<CallInst>(ins)){
							StringRef callName = cast<CallInst>(ins)->getCalledFunction()->getName();
							StringRef::iterator callNamei = callName.begin();
							if((*callNamei == 'p') && (!callName.equals("printf"))&&(!callName.equals("pop_direct_branch")) ){
								
								//replace called func with cloned func
								char* s = "_clone";
								StringRef newcallName = Twine(callName,s).str();
								Function* crClonedFc = mod.getFunction(newcallName);
								
								cast<CallInst>(ins)->setCalledFunction(crClonedFc);


								//retrieve global
								ins = ins->getNextNode();
								if(isa<StoreInst>(ins)){
									errs()<<"Met Store Instruction"<<'\n';
									Value * Va = ins->getOperand(1);
									
									
									
									LoadInst* loadGlo = new LoadInst(gvar_int32_gloVariable, "", false, block);
									loadGlo->setAlignment(4);
									loadGlo->removeFromParent();
									loadGlo->insertBefore(ins);
									StoreInst* getGlo = new StoreInst(loadGlo, Va, false, block);
									getGlo->setAlignment(4);
									getGlo->removeFromParent();
								
									//getGlo->insertBefore(ins);
									BasicBlock::iterator midi = ins;
									ReplaceInstWithInst(ins->getParent()->getInstList(), midi, getGlo);
									ins = midi;							
								}else{
									unsigned Opnum = ins->getNumOperands();
									while(Opnum--){
										Value* val = ins->getOperand(Opnum);
										if(isa<CallInst>(val)){
											LoadInst* loadGlo = new LoadInst(gvar_int32_gloVariable, "", false, block);
											loadGlo->setAlignment(4);
											loadGlo->removeFromParent();
											loadGlo->insertBefore(ins);
											ins->replaceUsesOfWith(val, loadGlo);
										}else{
											errs()<<"Not a Call"<<'\n';
										}
									}
								}
							}
												
								
						}
						ins = ins->getNextNode();
					}
					block = block->getNextNode();
				}
			}else{errs()<<"called pop_direct_branch"<<'\n';}
		}
		i = i->getNextNode();
	}	
	//retrieve after call end
		
	errs()<<"STAGE 3 pass"<<'\n';
	free(clonedFs);
	}
};
}
char Clonefunc::ID = 0;
static RegisterPass<Clonefunc> X("Clonefunc", "Clonefunc Pass", false, false);