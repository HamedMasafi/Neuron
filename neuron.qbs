import qbs

Product {
    type: "staticlibrary"
    name: "neuron"
    property string peerType: ""
    Depends { name: "cpp" }
    Depends { name: "Qt.core" }
    Depends { name: "Qt.network" }

    Export {
        Depends { name: "cpp" }
        Depends { name: "Qt.core" }
        Depends { name: "Qt.network" }
        cpp.includePaths: [
            product.sourceDirectory + "/src",
            product.sourceDirectory + "/include"
        ]

        cpp.defines: [
            product.peerType === "server" ? "NEURON_SERVER" :
                                    product.peerType === "client" ? "NEURON_CLIENT" :
                                                            "NEURON_NO_TYPE"
        ]
    }

    files: [
        "src/neuronabstracthub.cpp",
        "src/neuronabstractserializer.cpp",
        "src/neuronjsonbinaryserializer.cpp",
        "src/neuronremotecall.cpp",
        "src/neuronclienthub.cpp",
        "src/neuronserverhub.cpp",
        "src/neuronserver.cpp",
        "src/neurontcpsocketserver.cpp",
        "src/neuronsharedobject.cpp",
        "src/neuronpeer.cpp",
        "src/neuronserverthread.cpp",
        "src/neuronabstractdataencoder.cpp",
        "src/neuronsimpletokenvalidator.cpp"
    ]
}
