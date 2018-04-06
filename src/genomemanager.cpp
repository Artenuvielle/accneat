#include "util/std.h" // Must be included first. Precompiled header with standard library includes.
#include "genomemanager.h"
#include "innovgenome/innovgenomemanager.h"
#include "util/util.h"

using namespace NEAT;

GenomeManager *GenomeManager::create() {
    switch(env->genome_type) {
    case GenomeType::INNOV:
        return new InnovGenomeManager();
    default:
        panic();
    }
}
