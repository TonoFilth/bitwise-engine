premake.modules.android = {}
local android = premake.modules.android

newaction
{
    trigger = "android",
    description = "Generates Android.mk files",

    onStart = function()
        premake.escaper(android.escaper)
        print("Starting Lua generation")
    end,

    onWorkspace = function(workspace)
        printf("Generating Lua for workspace '%s'", workspace.name)
    end,

    onProject = function(project)
        --printf("Generating Lua for project '%s'", project.name)
        premake.generate(project, ".mk", android.generateProject)
    end,

    execute = function()
        print("Executing Lua action")
    end,

    onEnd = function()
        print("Lua generation complete")
    end
}

function android.print_table(t, level, maxTables)
    if maxTables == 8 then
        return
    end

    local indent = string.rep(" ", level * 2)

    for k,v in pairs(t) do
        if type(v) == "table" then
            if type(k) == "table" then
                print(indent .. "[table]")
            else
                print(indent .. "[" .. k .. "]")
            end

            --if k == "configs" or k == "Debug_SOx64" or k == "linktarget" then
                android.print_table(v, level + 1, maxTables + 1)
            --end
            --print(indent .. "Table: " .. k)
            --android.print_table(v, level + 1, maxTables + 1)
        elseif type(v) == "boolean" then
            if v == true then
                print(indent .. "[" .. k .. "] => true")
            else
                print(indent .. "[" .. k .. "] => false")
            end
        elseif type(v) == "userdata" then
            print(indent .. "[" .. k .. "] => userdata")
        elseif type(v) == "function" then
            print(indent .. "[" .. k .. "] => function")
        else
            print(indent .. "[" .. k .. "] => " .. v)
        end
    end
end

function android.getNbConfigs(project)
    local count = 0

    for _ in pairs(project.configs) do
        count = count + 1
    end

    return count
end

function android.getConfig(project, configIndex)
    local count = 0

    for k,v in pairs(project.configs) do
        count = count + 1
        if count == configIndex then
            return v
        end
    end

    return nil
end

function android.writeConfig(config)
    premake.w("# Start config")
    premake.w('ifdef %s', config.buildcfg)

    premake.push('LOCAL_SRC_FILES := \\')
    for i,file in ipairs(config.files) do
        if path.getextension(file) == ".cpp" then
            premake.w('%s \\', file)
        end
    end
    premake.pop('')

    premake.push('LOCAL_C_INCLUDES := \\')
    for k,dir in ipairs(config.includedirs) do
        premake.w('%s \\', dir)
    end
    premake.pop('')

    local toolset = premake.tools[config.toolset or "gcc"]
    local defines = toolset.getdefines(config.defines)

    premake.push('LOCAL_C_FLAGS := \\')
    for k,define in pairs(defines) do
        premake.w('%s=1 \\', define)
    end
    premake.pop('')

    if config.kind == "SharedLib" then
        premake.w('include $(BUILD_SHARED_LIBRARY)')
    elseif config.kind == "StaticLib" then
        premake.w('include $(BUILD_STATIC_LIBRARY)')
    end

    premake.w('endif\n')
end

function android.generateProject(project)
    -- Get first config
    local cfg = android.getConfig(project, 1)

    premake.w('LOCAL_PATH := $(call my-dir)')
    premake.w('')
    premake.w('include $(CLEAR_VARS)')
    premake.w('')
    premake.w('LOCAL_MODULE := %s', cfg.targetname)

    for k,config in pairs(project.configs) do
        android.writeConfig(config)

        if config.buildcfg == "Release" then
            --android.print_table(config, 1, 1)
            --[[local toolset = premake.tools[config.toolset or "gcc"]
            local defines = toolset.getdefines(config.defines)

            for k,v in pairs(defines) do
                print(v)
            end--]]
        end
    end

    --android.print_table(project, 1, 1)
    --android.print_table(cfg, 1, 1)
end

function android.escaper(value)
    value = value:gsub('\\', '\\\\')
    value = value:gsub('"', '\\"')
    return value
end

return android