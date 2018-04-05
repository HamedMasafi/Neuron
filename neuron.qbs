import qbs

Product {
    type: "staticlibrary"
    name: ""
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
        "src/abstracthub.cpp",
        "src/abstractserializer.cpp",
        "src/jsonbinaryserializer.cpp",
        "src/remotecall.cpp",
        "src/clienthub.cpp",
        "src/serverhub.cpp",
        "src/server.cpp",
        "src/tcpsocketserver.cpp",
        "src/sharedobject.cpp",
        "src/peer.cpp",
        "src/serverthread.cpp",
        "src/abstractdataencoder.cpp",
        "src/simpletokenvalidator.cpp"
    ]
}
