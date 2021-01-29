//iteration
virtual bool runOnFunction(Function &F) {
		
		Function::iterator i = (&F)->begin();
		BasicBlock::iterator bi = i->begin();
		BasicBlock::iterator e = i->end();
      		//errs() << "Hello: ";
     		errs().write_escaped(F.getName()) << '\n';
		errs() << (*i).size() << '\n';
		
		while(1){
			if(bi == e){
				break;
			}else{errs() << *bi << '\n';}
			bi++;
		}

		  
      		return false;
    }	

//clone function
virtual bool runOnFunction(Function &F) {
		Function::iterator i = (&F)->begin();
		Function *newF;
		ValueToValueMapTy VMap;
		void* p;
		p=0;
		newF = llvm::CloneFunction(&F, VMap,p);
		
		errs() <<"cloned func name "<< newF->getName() <<'\n';
		errs() << "old func name "<<F.getName() << '\n';  
      		return false;
    	}	
//condition
virtual bool runOnFunction(Function &F) {
		Function::iterator i = (&F)->begin();
		
		if(F.getName().equals("pow2")){
			newF = llvm::CloneFunction(&F, VMap,NULL);
			errs() <<"cloned func name "<< newF->getName() <<'\n';
		}

		
		errs() << "old func name "<<F.getName() << '\n';  
      		return false;
    	}
//insert instructions

 virtual bool runOnFunction(Function &F) {
		Function::iterator i = (&F)->end();
		BasicBlock::iterator bi = i->begin();
		BasicBlock::iterator e = i->end();
		//LLVMContext &ctx = getGlobalContext();
		//M = F.getParent();
		//AllocaInst* pa = new AllocaInst(IntegerType::get(ctx, 32), 0, "indexLoc");
		//M.getContext();
		//i->getInstList().insert((bi), pa);
		//i->getInstList().push_back(pa);

		//IR.CreateAlloca(IntegerType::get(M.getContext(), 32), NULL, "a");
				
		errs() <<*bi << '\n';  
      		return false;
    	}	


virtual bool runOnFunction(Function &F) {
		Function::iterator i = (&F)->begin();
		BasicBlock::iterator bi = (i)->begin();
		//BasicBlock::iterator e = i->end();
      		
		LLVMContext &ctx = getGlobalContext();
		AllocaInst* pa = new AllocaInst(IntegerType::get(ctx, 32), 0, "indexLoc");
		
		//bi->eraseFromParent();
		bi->getParent()->getInstList().insert(bi, pa);
		
		errs() <<*bi << '\n';
		
		  
      		return false;
    	}	


//global variable 
LLVMContext &ctx = getGlobalContext();

	 GlobalVariable* gvar_int32_gloVariable = new GlobalVariable(/*Module=*/mod, 
 	/*Type=*/IntegerType::get(ctx, 32),
 	/*isConstant=*/false,
 	/*Linkage=*/GlobalValue::CommonLinkage,
 	/*Initializer=*/0, // has initializer, specified below
 	/*Name=*/"gloVariable");
 	gvar_int32_gloVariable->setAlignment(4);
 
 	// Constant Definitions
 	ConstantInt* const_int32_2 = ConstantInt::get(ctx, APInt(32, StringRef("0"), 10));
  	// Global Variable Definitions
 	gvar_int32_gloVariable->setInitializer(const_int32_2);



//model operation:
using namespace llvm;

namespace {
struct Hello :  public ModulePass
{
        /** Constructor. */
	static char ID;                           
	Hello() : ModulePass(ID) {}

	virtual bool runOnModule(Module &mod){
		mod.setModuleIdentifier("123");
	errs() << mod.getModuleIdentifier() << '\n';
	
	}

};
}

char Hello::ID = 0;
static RegisterPass<Hello> X("hello", "Hello World Pass", false, false);


//Module gets function by name 
virtual bool runOnModule(Module &mod){
		Function* fptr = mod.getFunction("main");
		mod.setModuleIdentifier("123");
	errs() << mod.getModuleIdentifier() << '\n';
	Function::iterator i = fptr->begin();
	errs() << (*i).size() << '\n';




//find function list from module
namespace {
struct Hello :  public ModulePass
{
        /** Constructor. */
	static char ID;                           
	Hello() : ModulePass(ID) {}

	virtual bool runOnModule(Module &mod){
	Module::FunctionListType &f = mod.getFunctionList();
	Function* i = (&f)->begin();
	errs() << (*i).getName() << '\n';
	
	mod.setModuleIdentifier("123");
	errs() << mod.getModuleIdentifier() << '\n';
	//Function::iterator i = fptr->begin();
	
	
	LLVMContext &ctx = getGlobalContext();

	 GlobalVariable* gvar_int32_gloVariable = new GlobalVariable(/*Module=*/mod, 
 	/*Type=*/IntegerType::get(ctx, 32),
 	/*isConstant=*/false,
 	/*Linkage=*/GlobalValue::CommonLinkage,
 	/*Initializer=*/0, // has initializer, specified below
 	/*Name=*/"gloVariable");
 	gvar_int32_gloVariable->setAlignment(4);
 
 	// Constant Definitions
 	ConstantInt* const_int32_2 = ConstantInt::get(ctx, APInt(32, StringRef("0"), 10));
  	// Global Variable Definitions
 	gvar_int32_gloVariable->setInitializer(const_int32_2);
	
	
		
	}
};







//iteration under modulepass:
#define DEBUG_TYPE "hello"
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
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/SymbolTableListTraits.h"


using namespace llvm;

namespace {
struct Hello :  public ModulePass
{
        /** Constructor. */
	static char ID;                           
	Hello() : ModulePass(ID) {}

	virtual bool runOnModule(Module &mod){
	Module::FunctionListType &f = mod.getFunctionList();
	Function* i = (&f)->begin();
	Function* e = (&f)->end();
	while(i != NULL){
		errs() << (*(i)).getName() << '\n';
		Function::BasicBlockListType &bList = i->getBasicBlockList();
		BasicBlock* block = (&bList)->begin();
		BasicBlock* blocke = (&bList)->end();
		while(block != blocke){
			BasicBlock::InstListType &inslist = block->getInstList();
			Instruction* ins = (&inslist)->begin();
			Instruction* inse = (&inslist)->end();
			while(ins != inse){
				errs() << (*ins) << '\n';
				ins = ins->getNextNode();
			}
			block = block->getNextNode();
		}
		i = i->getNextNode();
	}
		//errs() << (*(i)).getName() << '\n';
		
				
	//}
	
	
	mod.setModuleIdentifier("123");
	errs() << mod.getModuleIdentifier() << '\n';
	//Function::iterator i = fptr->begin();
	
	

	LLVMContext &ctx = getGlobalContext();

	 GlobalVariable* gvar_int32_gloVariable = new GlobalVariable(/*Module=*/mod, 
 	/*Type=*/IntegerType::get(ctx, 32),
 	/*isConstant=*/false,
 	/*Linkage=*/GlobalValue::CommonLinkage,
 	/*Initializer=*/0, // has initializer, specified below
 	/*Name=*/"gloVariable");
 	gvar_int32_gloVariable->setAlignment(4);
 
 	// Constant Definitions
 	ConstantInt* const_int32_2 = ConstantInt::get(ctx, APInt(32, StringRef("0"), 10));
  	// Global Variable Definitions
 	gvar_int32_gloVariable->setInitializer(const_int32_2);
	
	
		
	}
};
}

char Hello::ID = 0;
static RegisterPass<Hello> X("hello", "Hello World Pass", false, false);


//iterator method under modulepass:
namespace {
struct Hello :  public ModulePass
{
        /** Constructor. */
	static char ID;                           
	Hello() : ModulePass(ID) {}

	virtual bool runOnModule(Module &mod){
		Module::iterator j = (&mod)->begin();
		Function::iterator i = j->begin();
		BasicBlock::iterator bi = i->begin();
		BasicBlock::iterator e = i->end();
      		//errs() << "Hello: ";
     		//errs().write_escaped(.getName()) << '\n';
		//errs() << (*i).size() << '\n';
		
		while(1){
			if(bi == e){
				break;
			}else{errs() << *bi << '\n';}
			bi++;
		}

		  
      		return false;	
	
		
	}
};
}


//while iteration:
Module::FunctionListType &f = mod.getFunctionList();
	Function* i = (&f)->begin();
	Function* e = (&f)->end();
	while(i != NULL){
		errs() << (*(i)).getName() << '\n';
		Function::BasicBlockListType &bList = i->getBasicBlockList();
		BasicBlock* block = (&bList)->begin();
		BasicBlock* blocke = (&bList)->end();
		while(block != blocke){
			BasicBlock::InstListType &inslist = block->getInstList();
			Instruction* ins = (&inslist)->begin();
			Instruction* inse = (&inslist)->end();
			while(ins != inse){
				errs() << (*ins) << '\n';
				if (isa<CallInst>(ins)){
					if(!(cast<CallInst>(ins)->getCalledFunction()->getName().equals("printf"))){
						
						errs()<<"yes"<<'\n';
						errs()<<cast<CallInst>(ins)->getCalledFunction()->getName()<<'\n';
						
					}	
				}
				ins = ins->getNextNode();
			}
			block = block->getNextNode();
		}
		i = i->getNextNode();
	}	
