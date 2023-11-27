//
//  ModelSelector.h
//  C6 Code
//
//  Created by Avijeet Trivedi on 07/04/20.
//  Copyright � 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef ModelSelector_h
#define ModelSelector_h

/******************************************************************************************
 MODEL = 0 : SW Only
 MODEL = 1 : HW_SW with Lite
 MODEL = 2 : HW_SW with Lite Upgrade
 MODEL = 3 : HW_SW with Stream
 MODEL = 4 : HW_SW with Stream Upgrade
 ********************************************************************************************/

/******************************************************************************************
 TS = 0 : AlphaBeta
 TS = 1 : AlphaBeta With Memory
 TS = 2 : NegaMax
 TS = 3 : NegaMax With Memory
 TS = 4 : NegaScout With Memory
 ********************************************************************************************/

#if (MODEL==1 || MODEL==2)
unsigned int* address = (unsigned int*) XPAR_THREAT_ANALYZER_LITE_0_S00_AXI_BASEADDR ;
#endif

#if (MODEL==3 || MODEL==4)
#include "xaxidma.h"
#define DMA_DEV_ID          XPAR_AXIDMA_0_DEVICE_ID
#define NUM_OF_REGISTER     23
XAxiDma AxiDma;   //Device instance definitions
unsigned int* address = (unsigned int*) XPAR_CONNECT6_STREAMIP_0_S00_AXI_BASEADDR ;
#endif

#if (MODEL==3 || MODEL==4)
void initialise_dma(int DeviceId)
{
	XAxiDma_Config *CfgPtr;

	// Initialize the XAxiDma device.
	CfgPtr = XAxiDma_LookupConfig(DeviceId);

	XAxiDma_CfgInitialize(&AxiDma, CfgPtr);

	// Disable interrupts, we use polling mode
	XAxiDma_IntrDisable(&AxiDma, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DEVICE_TO_DMA);
	XAxiDma_IntrDisable(&AxiDma, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DMA_TO_DEVICE);
}
#endif

#if(MODEL==0 && TS==0)
#include "TC_NO.h"
#include "TC_SW.h"
#include "NodeOrdering.h"
#include "ThreatFinder.h"
#include "MoveSelector.h"
#include "AlphaBeta.h"
#include "FBM_AB.h"

#elif(MODEL==4 && TS==0)
#include "TC_NO_HW.h"
#include "TC_STREAM_UPG.h"
#include "TC_SW.h"
#include "NodeOrdering.h"
#include "ThreatFinder.h"
#include "MoveSelector.h"
#include "AlphaBeta_UPG.h"
#include "FBM_AB.h"

#elif(MODEL==0 && TS==1)
#include "TranspositionTable.h"
#include "TC_SW.h"
#include "NodeOrdering.h"
#include "ThreatFinder.h"
#include "MoveSelector.h"
#include "AlphaBetaWithMemory.h"
#include "FBM_AB.h"

#elif(MODEL==0 && TS==2)
#include "TC_SW.h"
#include "NodeOrdering.h"
#include "ThreatFinder.h"
#include "MoveSelector.h"
#include "NegaMax.h"
#include "FBM_NS.h"

#elif(MODEL==0 && TS==3)
#include "TranspositionTable.h"
#include "TC_SW.h"
#include "NodeOrdering.h"
#include "ThreatFinder.h"
#include "MoveSelector.h"
#include "NegaMaxWithMemory.h"
#include "FBM_NS.h"

#elif(MODEL==0 && TS==4)
#include "TranspositionTable.h"
#include "TC_SW.h"
#include "TC_NO.h"
#include "NodeOrdering.h"
#include "ThreatFinder.h"
#include "MoveSelector.h"
#include "NegaScout.h"
#include "FBM_NS.h"

#elif(MODEL==4 && TS==4)
#include "TC_NO_HW.h"
#include "TranspositionTable.h"
#include "TC_STREAM_UPG.h"
#include "NodeOrdering.h"
#include "ThreatFinder.h"
#include "MoveSelector.h"
//#include "NegaMax.h"
#include "NegaScout_UPG.h"
#include "FBM_NS.h"

#elif(MODEL==3 && TS==4)
#include "TC_NO_HW.h"
#include "TranspositionTable.h"
#include "TC_STREAM.h"
#include "NodeOrdering.h"
#include "ThreatFinder.h"
#include "MoveSelector.h"
#include "NegaScout.h"
#include "FBM_NS.h"


#elif(MODEL==1 && TS==0)
#include "TC_LITE.h"
#include "NodeOrdering.h"
#include "ThreatFinder.h"
#include "MoveSelector.h"
#include "AlphaBeta.h"
#include "FBM_AB.h"

#elif(MODEL==2 && TS==0)
#include "TC_LITE_UPG.h"
#include "NodeOrdering.h"
#include "ThreatFinder.h"
#include "MoveSelector.h"
#include "AlphaBeta.h"
#include "FBM_AB.h"

#elif(MODEL==3 && TS==0)
#include "TC_NO.h"
#include "TC_STREAM.h"
#include "NodeOrdering.h"
#include "ThreatFinder.h"
#include "MoveSelector.h"
#include "AlphaBeta.h"
#include "FBM_AB.h"

#elif(MODEL==1 && TS==4)
#include "TranspositionTable.h"
#include "TC_LITE.h"
#include "NodeOrdering.h"
#include "ThreatFinder.h"
#include "MoveSelector.h"
#include "NegaScout.h"
#include "FBM_NS.h"

#elif(MODEL==2 && TS==4)
#include "TranspositionTable.h"
#include "TC_LITE_UPG.h"
#include "NodeOrdering.h"
#include "ThreatFinder.h"
#include "MoveSelector.h"
#include "NegaScout_UPG.h"
#include "FBM_NS.h"

#endif





#endif /* ModelSelector_h */
