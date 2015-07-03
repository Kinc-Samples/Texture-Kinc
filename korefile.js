var solution = new Solution('TextureTest');
var project = new Project('TextureTest');

project.addFile('Sources/**');
project.setDebugDir('Deployment');

project.addSubProject(Solution.createProject('Kore'));

solution.addProject(project);

return solution;
