add_subdirectory(azimuth)
add_subdirectory(carbonGas)
add_subdirectory(Cradius)
add_subdirectory(Ctheta)
add_subdirectory(CX)
add_subdirectory(CY)
add_subdirectory(doppler)
add_subdirectory(instantCurrent)
add_subdirectory(jetEngine)
add_subdirectory(leadLag)
add_subdirectory(triangle)
add_subdirectory(turbine)

add_custom_target(fpbench)
add_dependencies(fpbench
    azimuth.all
    # carbonGas.all
    Cradius.all
    Ctheta.all
    CX.all
    CY.all
    doppler.all
    instantCurrent.all
    jetEngine.all
    leadLag.all
    triangle.all
    turbine.all)

add_custom_target(fpbench.ppu)
add_dependencies(fpbench.ppu
    azimuth.vsimc
    carbonGas.vsimc
    Cradius.vsimc
    Ctheta.vsimc
    CX.vsimc
    CY.vsimc
    doppler.vsimc
    instantCurrent.vsimc
    jetEngine.vsimc
    leadLag.vsimc
    triangle.vsimc
    turbine.vsimc)

add_custom_target(fpbench.float)
add_dependencies(fpbench.float
    azimuth.float.vsimc
    carbonGas.float.vsimc
    Cradius.float.vsimc
    Ctheta.float.vsimc
    CX.float.vsimc
    CY.float.vsimc
    doppler.float.vsimc
    instantCurrent.float.vsimc
    jetEngine.float.vsimc
    leadLag.float.vsimc
    triangle.float.vsimc
    turbine.float.vsimc)

add_custom_target(fpbench.fixp)
add_dependencies(fpbench.fixp
    azimuth.fixp.vsimc
    # carbonGas.fixp.vsimc
    Cradius.fixp.vsimc
    Ctheta.fixp.vsimc
    CX.fixp.vsimc
    CY.fixp.vsimc
    doppler.fixp.vsimc
    instantCurrent.fixp.vsimc
    jetEngine.fixp.vsimc
    leadLag.fixp.vsimc
    triangle.fixp.vsimc
    turbine.fixp.vsimc)

add_custom_target(fpbench.validate
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/validate.py ${CMAKE_CURRENT_BINARY_DIR}
            azimuth Cradius Ctheta CX CY doppler instantCurrent jetEngine leadLag triangle turbine)
