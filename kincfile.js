const project = new Project('TextureTest');

project.addFile('Sources/**');
project.addFile('Shaders/**');
project.setDebugDir('Deployment');

resolve(project);
