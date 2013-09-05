function setFilter(persistence, gain) {
    Module.ccall('setFilter', 'void', ['float', 'float'], [persistence, gain]);
}
Module['setFilter'] = setFilter;

function find (canvas) {
    var ctx = canvas.getContext('2d');
    var inputBuf = Module._malloc(canvas.width*canvas.height);
    var img = ctx.getImageData(0, 0, canvas.width, canvas.height);
    var binary = new Uint8Array(img.data.length/4);
    for(var i=0; i<binary.length; i++){
        setValue(inputBuf+i, Math.min(0.299 * img.data[4*i] + 0.587 * img.data[4*i+1] + 0.114 * img.data[4*i+2], 255), "i8");
    }
    var output = Module.ccall('find', 'string', ['int', 'int', 'int'], [inputBuf, canvas.width, canvas.height]);
    Module._free(inputBuf);
    return JSON.parse(output);
}
Module['find'] = find;

function set2DFilter(persistence, gain) {
    Module.ccall('set2DFilter', 'void', ['float', 'float'], [persistence, gain]);
}
Module['set2DFilter'] = set2DFilter;

function set3DFilter(persistence, gain) {
    Module.ccall('set3DFilter', 'void', ['float', 'float'], [persistence, gain]);
}
Module['set3DFilter'] = set3DFilter;

//Detect tags and return JSON object including pairs of tag name and its transformation matrix
function estimate (canvas, rectification) {
    var ctx = canvas.getContext('2d');
    var inputBuf = Module._malloc(canvas.width*canvas.height);
    var img = ctx.getImageData(0, 0, canvas.width, canvas.height);
    var binary = new Uint8Array(img.data.length/4);
    for(var i=0; i<binary.length; i++){
        setValue(inputBuf+i, Math.min(0.299 * img.data[4*i] + 0.587 * img.data[4*i+1] + 0.114 * img.data[4*i+2], 255), "i8");
    }
    var output = Module.ccall('estimate', 'string', ['int', 'int', 'int', 'boolean'], [inputBuf, canvas.width, canvas.height, rectification]);
    var obj = JSON.parse(output);

    if(rectification){
        var outputImage = ctx.createImageData(canvas.width, canvas.height);
        for(var i=0; i<canvas.width*canvas.height; i++){
            var val = getValue(inputBuf+i, "i8");
            if(val<0) val += 255;
            outputImage.data[4*i] = val;
            outputImage.data[4*i+1] = val;
            outputImage.data[4*i+2] = val;
            outputImage.data[4*i+3] = 255;
        }
        ctx.putImageData(outputImage, 0, 0);
    }
    Module._free(inputBuf);
    return obj
}
Module['estimate'] = estimate;

//Set marker configuration
var tagConfigFileNumber = 1;
function readTagConfiguration(file, omitOtherTags, callback) {
    var reader = new FileReader;
    reader.readAsArrayBuffer(file);
    reader.onload = function() {
        var fileName = 'markerConfigration' + tagConfigFileNumber;
        var node = FS.createDataFile('/', fileName, new Uint8Array(reader.result), true, true);
        tagConfigFileNumber++;
        Module.ccall('readTagConfiguration', 'void', ['string', 'boolean'], [fileName, omitOtherTags]);
        callback();
    }
}
Module['readTagConfiguration'] = readTagConfiguration;

function setDefaultTagSize(defaultSize) {
    Module.ccall('setDefaultTagSize', 'void', ['float'], [defaultSize]);
}
Module['setDefaultTagSize'] = setDefaultTagSize;

//Set new camera calibration
var cameraCalibrationFileNumber = 1;
function readCalibration(file, callback) {
    var reader = new FileReader;
    reader.readAsArrayBuffer(file);
    reader.onload = function() {
        var fileName = 'cameraConfiguration' + cameraCalibrationFileNumber;
        var node = FS.createDataFile('/', fileName, new Uint8Array(reader.result), true, true);
        cameraCalibrationFileNumber++;
        Module.ccall('readCalibration', 'void', ['string'], [fileName]);
        callback();
    }
}
Module['readCalibration'] = readCalibration;

//Return projection matrix
function getCameraMatrix() {
    var buf = Module._malloc(4*9);
    Module.ccall('getCameraMatrix', 'void', ['int'], [buf]);
    var matrix = new Float32Array(9);
    for(var i=0; i<matrix.length; i++){
        matrix[i] = getValue(buf+4*i, "float");
    }
    Module._free(buf);
    return matrix;
}
Module['getCameraMatrix'] = getCameraMatrix;

//Return projection matrix
function getDistortionCoeffs() {
    var buf = Module._malloc(4*5);
    var size = Module.ccall('getDistortionCoeffs', 'int', ['int'], [buf]);
    var matrix = new Float32Array(size);
    for(var i=0; i<matrix.length; i++){
        matrix[i] = getValue(buf+4*i, "float");
    }
    Module._free(buf);
    return matrix;
}
Module['getDistortionCoeffs'] = getDistortionCoeffs;

this['Chilitags'] = Module;
