// addrspace.h 
//	Data structures to keep track of executing user programs 
//	(address spaces).
//
//	For now, we don't keep any information about address spaces.
//	The user level CPU state is saved and restored in the thread
//	executing the user program (see thread.h).
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#ifndef ADDRSPACE_H
#define ADDRSPACE_H

#include "copyright.h"
#include "filesys.h"

#define UserStackSize		1024 	// increase this as necessary!

class AddrSpace {
  public:
    AddrSpace(OpenFile *executable, char * filename);	// Create an address space,
					// initializing it with the program
					// stored in the file "executable"
    OpenFile* exec_ptr;
    AddrSpace (AddrSpace *parentSpace);	// Used by fork
    int shm_all(int size);
    ~AddrSpace();			// De-allocate an address space

    void InitRegisters();		// Initialize user-level CPU registers,
					// before jumping to user code
    int handle_PFE(int vpn);
    void SaveState();			// Save/restore address space-specific
    void RestoreState();		// info on a context switch

    int replace(int algo, int ppn);
    unsigned GetNumPages();

    TranslationEntry* GetPageTable();
    void initbackup(int size);


  private:
    TranslationEntry *pageTable;	// Assume linear page table translation
					// for now!
    char * backup;
    char * char_exec;
    unsigned int numPages;		// Number of pages in the virtual 
					// address space
};

#endif // ADDRSPACE_H
