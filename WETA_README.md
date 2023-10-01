How to build & compile
----------------------

  oz / --using /weta/software/dev --cwd 

  whab configure --version ${USER}-staging
  whab  # <-- builds the DefaultVariant defined in habitat.yml

  whab all # <-- builds all
  whab test # <-- runs the tests on all VPs

at that point, you should have all the VP built, and a pak you can oz in

How to contribute
-----------------

- Check out the `weta/*.*.*` branch relevant to the version of materialX you want to contribute to
- create a new branch `weta/user/${USER}/MyChange` for your changes
- create a MR on Gitlab with your changes, merging into the relevant `weta/*.*.*` you've branched of
- get your changes reviewed by a team-member


How to release
--------------

On Gitlab - create a tag on the relevant `weta/vX.Y.Z` branch, representing your
version you want to release e.g. `weta/x.y.z-weta.w`

Create a /src folder for the release you're going to make 

    setenv MYVERSION = 'x.y.z-weta.w'
    mkdir /vol/weta/linux64/materialx/${MYVERSION}
    mkdir /vol/weta/linux64/materialx/${MYVERSION}/src
    cd /vol/weta/linux64/materialx/${MYVERSION}/src
    git clone gitlab@gitlab.wetafx.co.nz:habitat/platform/oss/materialx.git .

Check out the tag you want to release 

    git checkout weta/x.y.z-weta.w

Set up environment & Release
    
    oz / --using /weta/software/dev --cwd 
    whab release --ver ${MYVERSION}
     



Tests
------------
Running the tests shipped with materialX

VP19/DBG - All tests succeed (65/65)
VP20py2/DBG - All tests succeed (65/65)
VP21/DBG - All tests succeed (65/65)
VP22/DBG - All tests succeed (65/65)
