from setuptools import setup

package_name = 'py_pubsub'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='root',
    maintainer_email='root@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
		'image_source_video = py_pubsub.image_source_video:main',
		'talker = py_pubsub.publisher_member_function:main',
  		 'listener = py_pubsub.subscriber_member_function:main',
		'simple_publish = py_pubsub.simple_publish:main',
        ],
    },
)
