// **********************************************************************
// * FILE  : TecAlgorithm.h
// * GROUP : TecLibs/Algorithm
// *---------------------------------------------------------------------
// * PURPOSE : Algorithm classes
// * COMMENT : ...
// *---------------------------------------------------------------------
// * DATES     : 29/06/2000
// * AUTHORS   : Loic Le Chevalier (llechevalier@fr.infogrames.com)
// *             Cédric Guérin  (cguerin@fr.infogrames.com)
// * COPYRIGHT : (c) Infogrames/TecLab 2000
// **********************************************************************
#ifndef _TecAlgorithm_h_
#define _TecAlgorithm_h_



// ----------------------------------------------------------------------
// +---------
// | Algorithm section
// +---------
#include "TecLibs.h"                // To be Tec

#ifdef TEC_USE_NAMESPACES
	namespace TecAlgorithm {
#endif

#include "Algorithm/Reference.h"	// To use Reference / RefTarget
#include "Algorithm/FastAllocator.h"// To use FastAllocator
#include "Algorithm/LinkedList.h"   // To use LinkedList
#include "Algorithm/SortedList.h"   // To use SortedList
#include "Algorithm/SLinkedList.h"  // To use SLinkedList
#include "Algorithm/BitArray.h"		// To use BitArray
#include "Algorithm/DynArray.h"		// To use DynArray
#include "Algorithm/QuadTree.h"     // To use QuadTree
#include "Algorithm/Octree.h"       // To use Octree
		
#include "Algorithm/LinkedList.inl"
#include "Algorithm/SortedList.inl"
#include "Algorithm/SLinkedList.inl"
#include "Algorithm/BitArray.inl"
#include "Algorithm/DynArray.inl"
#include "Algorithm/QuadTree.inl"
#include "Algorithm/Octree.inl"
		
#ifdef TEC_USE_NAMESPACES
	}

	#define TecReference TecAlgorithm::Reference
	typedef TecAlgorithm::RefTarget TecRefTarget;
	#define TecFastAllocator TecAlgorithm::FastAllocator
	#define TecLinkedList TecAlgorithm::LinkedList
	#define TecSortedList TecAlgorithm::SortedList
	#define TecSLinkedList TecAlgorithm::SLinkedList
	typedef TecAlgorithm::BitArray TecBitArray;
	#define TecDynArray TecAlgorithm::DynArray
	#define TecQuadTree TecAlgorithm::QuadTree
	#define TecOctree TecAlgorithm::Octree
	
	using namespace TecAlgorithm;
#else
	typedef RefTarget TecRefTarget;
	#define TecReference Reference
	#define TecFastAllocator FastAllocator
	#define TecLinkedList LinkedList
	#define TecSortedList SortedList
	#define TecSLinkedList SLinkedList
	typedef BitArray TecBitArray;
	#define TecDynArray DynArray
	#define TecQuadTree QuadTree	
	#define TecOctree Octree
#endif
		
#endif//_Algorithm_h_