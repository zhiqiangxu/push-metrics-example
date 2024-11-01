#include <prometheus/counter.h>
#include <prometheus/registry.h>
#include <prometheus/gateway.h>
#include <thread> // Required for std::this_thread
#include <chrono> // Required for std::chrono::seconds
#include <iostream>
#include <unistd.h>

static std::string GetHostName()
{
    char hostname[1024];

    if (::gethostname(hostname, sizeof(hostname)))
    {
        return {};
    }
    return hostname;
}

int main()
{
    using namespace prometheus;

    // create a push gateway
    const auto labels = Gateway::GetInstanceLabel(GetHostName());

    Gateway gateway{"139.196.147.220", "9091", "sample_client", labels};

    auto registry = std::make_shared<Registry>();
    auto &gauge_family =
        BuildGauge().Name("hashrate").Help("").Register(*registry);
    auto &gauge = gauge_family.Add({{"address", "xxxx"}});
    // ask the pusher to push the metrics to the pushgateway
    gateway.RegisterCollectable(registry);

    for (int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        gauge.Set(i + 100.9f);
        // push metrics
        auto returnCode = gateway.Push();
        std::cout << "returnCode is " << returnCode << std::endl;
    }
    return 0;
}