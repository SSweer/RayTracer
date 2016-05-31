# RayTracer

Started as a school project and has been refactored and improved twice. It is a visual studio project, but I have not included the VS project files.

Parser extracts command line arguments.
Scene controls the ray tracing, and creates a ray per screen pixel.
RayTracer keeps pointers to all objects and lights in the scene, checks for intersections, creates light/reflection rays, and manages coloring.
Shape is an interface for Triangle and Circle, which check for intersections with themselves, calculate normals, and maintain references to their material attributes.
Light is an interface for PointLight and DirectionalLight, which both create rays and color objects.
