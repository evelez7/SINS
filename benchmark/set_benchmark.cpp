#include "set.hpp"
#include <benchmark/benchmark.h>
#include <random>

std::mt19937 gen;
std::random_device rd;

static void InsertSetup(const benchmark::State &state)
{
  gen.seed(rd());
}

static void RemoveSetup(const benchmark::State &state) {}

static void BM_SetInsertAVLTree(benchmark::State &state)
{
  std::vector<int> data;
  data.reserve(100);
  data.resize(100);
  std::uniform_int_distribution<> dist(-30000, 30000);
  for (unsigned i = 0; i < data.size(); ++i)
  {
    data.push_back(dist(gen));
  }
  ev::set<int> set;
  for (auto _ : state)
  {
    for (unsigned i = 0; i < data.size(); ++i)
    {
      set.insert(dist(gen));
    }
  }
}
BENCHMARK(BM_SetInsertAVLTree)->Setup(InsertSetup);

static void BM_SetInsertBST(benchmark::State &state)
{
  std::vector<int> data;
  data.reserve(100);
  data.resize(100);
  std::uniform_int_distribution<> dist(-30000, 30000);
  for (unsigned i = 0; i < data.size(); ++i)
  {
    data.push_back(dist(gen));
  }
  ev::set<int> set;
  for (auto _ : state)
  {
    for (unsigned i = 0; i < data.size(); ++i)
    {
      set.insert(data[i]);
    }
  }
}
BENCHMARK(BM_SetInsertBST)->Setup(InsertSetup);

BENCHMARK_MAIN();
